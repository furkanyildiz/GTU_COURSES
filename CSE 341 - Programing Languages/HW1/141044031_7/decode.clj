; *********************************************
; *  341 Programming Languages                *
; *  Fall 2017                                *
; *  Author: Fürkan YILDIZ                    *
; *********************************************


(ns clojure_hw1_yildiz_furkan) ;define namespace
;; utility functions


;verilen dosyayı okur ve her wordun karakterlerini ayrı ayrı bir listeye koyar ve tüm bu listelerin
;beraber olduğu bir liste oluşturur.
(defn read-as-list
	"Reads a file containing one word per line and returns a list of words (each word is in turn a list of characters)."
	[filename]
    (try
    (catch Exception e (println (str "caught exception: " (.getMessage e)))))

    (let [words (clojure.string/split (clojure.string/trim (slurp filename)) #"\s+")]
        (map #(map (comp symbol str) %) words)))

;; -----------------------------------------------------
;; HELPERS
;; *** PLACE YOUR HELPER FUNCTIONS BELOW ***

; dictionaryde tek tek dolaşarak wordü arar
;bulunursa true, bulunmazsa false return eder.
(defn spell-checker-0
	[word] 
  (def listem (read-as-list "dictionary2.txt"))
	(loop [x 0]
  (when (not= x (count listem))
    (cond
    (= (apply str (nth listem x)) word) ;stringe cevirir
      (true? true)
    ( and (= x (dec (count listem))) (not= (apply str (nth listem x)) word) )
      (true? false)
    :else
      (recur (inc x))))))

;spell-checker-1 fonksiyonu için yazılmış yardımcı fonksiyon
(defn binsearch [listem target]
  (def uppercount (dec (count listem)))
  (loop [lower 0
        upper uppercount]
    (if (> lower upper) (true? false)
      (let [mid (quot (+ lower upper) 2)
            midvalue (apply str (nth listem mid))]
        (cond
          (> (compare midvalue target) 0) (recur lower (dec mid))
          (< (compare midvalue target) 0) (recur (inc mid) upper)
          (= (compare midvalue target) 0) (true? true))))))


; Dictionary içinde binary search algorithmasıyla wordu arar
;bulunursa true, bulunmazsa false return eder.
(defn spell-checker-1
	[word]

  (binsearch (read-as-list "dictionary2.txt") word))

;verilen alfabe ile o alfabenin tüm kombinasyonları üretilir.
;https://stackoverflow.com/questions/26076077/clojure-list-all-permutations-of-a-list/26076145
(defn permutations [s]
  (lazy-seq
   (if (seq (rest s))
     (apply concat (for [x s]
                     (map #(cons x %) (permutations (remove #{x} s)))))
     [s])))


;encoded-word -> decoded-word
;keys gönderilen permütasyon '(c e a b d) gibi
(defn decode-word [word keyss]
    (def decoded_letters (atom '()))
    (loop [i 0]
        (when (not= i (count (map str (seq word))))
            (reset! decoded_letters (conj @decoded_letters (get (zipmap  keyss '(a b c d e f g h i j k l m n o p q r s t u v w x y z)) (symbol(nth (map str (seq word)) i)))))
            (recur (inc i))))
    (apply str (reverse @decoded_letters)))

;verilen permütasyon listesindeki permütasyonları deneyerek paragrafı decode etmeye çalışır, 
;tüm paragrafı decode edene kadar permütasyonları dener.
(defn check-perm [perms paragraph]

    (def cur_word_count (atom 0)) ;current word in paragraph

    (loop [i 0]
        (when (not= i (count @perms))
            (if (spell-checker-1 (decode-word (apply str (nth paragraph @cur_word_count)) (nth @perms i)))
               ;map current-kelime ile eşleştiyse

                (do
                    (reset! cur_word_count (inc @cur_word_count)) ;current word in paragraph

                    (if (<= (count paragraph) (- 1 @cur_word_count))
                        (do
                            (nth @perms i)
                        )
                    )

                    (while (and  (> (count paragraph) @cur_word_count)
                                (spell-checker-1 (decode-word (apply str (nth paragraph @cur_word_count)) (nth @perms i))))

                        (do
                            (reset! cur_word_count (inc @cur_word_count))

                        )
                    )
                    (if (= (count paragraph) @cur_word_count )
                        (do

                            (nth @perms i)
                        )
                        ;else durumu
                        (do 
                            (if (= i (- (count @perms) 1))
                                (do
                                    (empty '())
                                )
                                (do
                                    (reset! cur_word_count 0)
                                    (recur (inc i))
                                )
                            )
                        );diğer kelimerler ile eşleşmeyen map bulunmuş, yeni map aranmalı(tüm kelimelr için en baştan).
                    )

                )
                ;map current-kelime ile eşleşmediyse
                (do
                    ;son permüstasyon denenmiş ve son permüstasyonda decode edememişse
                    (if (= i (- (count @perms) 1))
                    
                        (do 
                            ;(true? false) ;bitti decode map bulunamadı
                            (empty '())
                        )
                        (do
                            (reset! cur_word_count  0)
                               (recur (inc i))
                        )
                    )
                )
            )
        )
    )
)

;perms must be atom type
;freq eslesmesine uymayan permutasyonlar silinecek bu fonksiyon yardımı ile.
(defn remove_from_perm [perms_atom index]
  (vec (concat (subvec @perms_atom 0 index) (subvec @perms_atom (inc index) (count @perms_atom)))))

;verilen paragarftaki en çok tekrar eden n harfi return eder.
(defn most-frequent-n [paragraph n ]
    ;paragrafı stringe çeviriyoruz
    (def d (atom '()))
    (loop [x 0]      
        (when (< x (count paragraph))
            (reset! d (conj @d (apply str (nth paragraph x))))
            (recur (inc x))
        )
    )
    (def s (apply str @d))
    ;daha sonra bu stringde frequencilere bakıyoruz
    (def items (sort-by val(frequencies (into [] (seq (char-array (clojure.string/replace (clojure.string/trim s) #" " "")))))))
    (->> items frequencies (sort-by val) (take n) (map first)))


;verilen paragraftaki freqleri bulur, bulduğu bu freqler, ingiliz alfabesindeki freqlere karşılık gelmelidir.
;bu durumu oluşturmak için, tüm permütasyonlardan, decoded dil ile ingiliz alfabesindeki freqlerin eşleşmediği
;permütasyonları çıkartır. Böylece freqleri freqler ile eşleşen diğer harfleri ise brute search ile yapan permü-
;tasyonlar üretir.
(defn freq_perms [paragraph]
    (def perms (permutations '(a b c d e f g h i j k l m n o p q r s t u v w x y z)))

    (def freq_letters (keys (into {} ( most-frequent-n paragraph 6))))
    (def english_freq_list #{"a" "e" "i" "o" "t" "n"})

    (def pv (atom(into [] perms)))
    (def index (atom 0))
    (while (not= @index (count @pv))
        (do(
            ;freqs letterlar a,e,i,o,t,n ye karşılık (o indexlere) test.txt deki freq decoded letterlar ollmalı
            ;bu kurala uymayan permüstasyonlar silinmeli.
            if  ((and(and(and (and (and (contains? english_freq_list (str(nth  (nth @pv @index)  0)) )
              (contains? english_freq_list (str(nth  (nth @pv @index)  4)) ))
              (contains? english_freq_list (str(nth  (nth @pv @index)  8)) ))
              (contains? english_freq_list (str(nth  (nth @pv @index)  13)) ))
              (contains? english_freq_list (str(nth  (nth @pv @index)  14)) ))
              (contains? english_freq_list (str(nth  (nth @pv @index)  19)) ))

              )
            
            (do
              (reset! index (inc @index))
            )
            (do
              (reset! pv (remove_from_perm pv @index))
            ))
        )
    )
    @pv
)


;; -----------------------------------------------------
;; DECODE FUNCTIONS

;alfabedeki tüm kombinasyonları oluşturur ve sırasıyla o kombinasyonları sozlukte arar (her kelime için) ve en uygun
;eşleşme için alfabeyi çözer
(defn Gen-Decoder-A
	[paragraph]

    (fn[word] (decode-word word (check-perm (atom (permutations '(a b c d e f g h i j k l m n o p q r s t u v w x y z))) paragraph)))

)

(defn Gen-Decoder-B-0
  [paragraph]
    ;permütasyonumuzu freq letterları göz önünde bulundurarak olusturuyoruz.
    (fn[word] (decode-word word (check-perm (atom (into () (freq_perms paragraph))) paragraph)))

)

(defn Gen-Decoder-B-1
	[paragraph]
  	;you should implement this function
)

; kendisine verilen decode fonksiyonu ile tüm dökümanı decode ederek decoded stringi return eder.
(defn Code-Breaker
    [document decoder]
    ;you should implement this function
    (def paragraph (read-as-list document))


    ;documentteki her wordu, decoder fonksiyonu ile tek tek decode ederek listeye atar ve listeyi stringe cevirir
    ;böylece decode edilmiş paragrafı elde ederiz.
    (def x (atom (-(count paragraph) 1)))
    (def decoded_words (atom '()))
    (while ( >= @x 0 )
        (do
            ;(decode-word (nth paragraph 1)
            (reset! decoded_words (conj @decoded_words ((decoder paragraph) (apply str(nth paragraph @x)) )))
            (reset! decoded_words (conj @decoded_words " "))
            (reset! x (dec @x))
        )
    )
    (apply str @decoded_words)
    
)

;; -----------------------------------------------------
;; Test code...
(defn test_on_test_data
	[]
	(let [doc (read-as-list "document1.txt")]
		(println doc)
        (println (Code-Breaker "document1.txt" Gen-Decoder-A))
        (println (Code-Breaker "document1.txt" Gen-Decoder-B-0))

    )
)
(test_on_test_data)