; *********************************************
; *  341 Programming Languages                *
; *  Fall 2017                                *
; *  Author: Yakup Genc                       *
; *********************************************

;; utility functions
(require '[clojure.string :as cs])
(load-file "include.clj") ;; "c2i and "i2c"
(ns example.core (:require [clojure.math.combinatorics :as combo]))

(use 'clojure.java.io)


(defn read-as-list
	"Reads a file containing one word per line and returns a list of words (each word is in turn a list of characters)."
	[filename]
  ;filename = "C:\\Users\\yldzf\\Desktop\\Programing Languages\\Homeworks\\HW1\\test.txt"
  (def s (slurp filename))
  (let [words (cs/split (cs/trim s) #"\s+")]
    (map #(map (comp symbol str) %) words))
)
(def filename "C:\\Users\\yldzf\\Desktop\\Programing Languages\\Homeworks\\HW1\\test.txt")
(def dasd (read-as-list filename))
dasd
(foo dasd)
(apply str(nth dasd 0))
(count dasd)
(defn foo [paragraph]
    (def listeem23 (atom '[]))

    (loop [x 0]
      (when (< x (count paragraph))
        (split-word-2 (apply str(nth dasd x)) listeem23)
        (recur (inc x))))

  (println @listeem23)
)

(def s (slurp filename))
s
(nth s 0)
(def  (cs/split s #" ")

(loop [x 0]
  (when (< x (- (count word) 1))
    (reset! listee (conj @listee (str(nth word x) (nth word (inc x)))))
    (recur (inc x))))



(use 'clojure.string)
(def s1 (replace (trim s) #" " ","))
s1

(def den "fur")

den
(count den)
(def listeem (atom '[]))



(defn split-word-2 [word listee]
  (
  if(<= (count word) 2)

    (do
      (reset! listee (conj @listee word))
    )
    (do

  (loop [x 0]
      (when (< x (- (count word) 1))
          (reset! listee (conj @listee (str(nth word x) (nth word (inc x)))))
         (recur (inc x))))

      )))





(println @listeem)
(split-word-2 "selam" listeem)
(frequencies @listeem)
(println "denemeeeeee")
(clojure.string/trim s1)

(into [] (seq (char-array (replace (clojure.string/trim s) #" " ""))))

(sort-by val(frequencies (into [] (seq (char-array (replace (trim s) #" " ""))))))

(reverse (sort-by val (frequencies (replace (trim s) #" " "") )))
         (sort-by val (frequencies (into [] (seq (char-array s)))))
(reverse (sort-by val (frequencies (into [] (seq (char-array s))))))
(first (nth (reverse (sort-by val (frequencies (into [] (seq (char-array s)))))) 2))
(first (nth (reverse (sort-by val (frequencies (into [] (seq (char-array s)))))) 2))

(defn most-frequent-n [n]
  ;değiştir bu ilk satırı
  (def filename "C:\\Users\\yldzf\\Desktop\\Programing Languages\\Homeworks\\HW1\\test.txt")
  (def s (slurp filename))

  (def items (sort-by val(frequencies (into [] (seq (char-array (replace (trim s) #" " "")))))))
  (->> items
    frequencies
    (sort-by val)
    (take n)
    (map first)))

(keys (into {} ( most-frequent-n 3)))

(def freq_list (keys (into {} ( most-frequent-n 3))))

(.indexOf  freq_list (first(map char "a")))

(def freq_letters (keys (into {} ( most-frequent-n 3))))
freq_letters
(nth freq_letters 1)
(keys(into {}  ( most-frequent-n 3)))
(symbol(str(nth freq_letters 1)))

(map char "a")

(with-open [r (clojure.java.io/input-stream filename)]
         (loop [c (.read r)]
           (if (not= c -1)
             (do
               (println (char c))
               (recur (.read r))))))

(println "deneme")
(mapcat seq (line-seq s))
(doseq [c s] (println c))
(println (remove #{"\n"} s))
(with-open [reader (clojure.java.io/reader filename)])

(println s)



(with-open [rdr (clojure.java.io/reader filename)]
         (count (line-seq rdr)))

;; -----------------------------------------------------
;; HELPERS
;; *** PLACE YOUR HELPER FUNCTIONS BELOW ***

(read-as-list "C:\\Users\\yldzf\\Desktop\\Programing Languages\\Homeworks\\HW1\\dictionary2.txt")
(count listem)
(nth listem 45406)

(defn spell-checker-0
	[word]
  (def listem (read-as-list "C:\\Users\\yldzf\\Desktop\\Programing Languages\\Homeworks\\HW1\\dictionary2.txt"))
	(loop [x 0]
  (when (not= x (count listem))
  ;(println (nth listem x))
    (cond
    (= (apply str (nth listem x)) word) ;stringe cevirir
      (true? true)
    ( and (= x (dec (count listem))) (not= (apply str (nth listem x)) word) )
      (true? false)
    :else
      (recur (inc x))))

    )
)



;;-- lets do binary search

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


(defn spell-checker-1
	[word]


  (def dic_list (read-as-list "C:\\Users\\yldzf\\Desktop\\Programing Languages\\Homeworks\\HW1\\dictionary2.txt"))
  (binsearch dic_list word)

)



;; -----------------------------------------------------
;; DECODE FUNCTIONS

(defn Gen-Decoder-A
	[paragraph]
	;you should implement this function
)

(defn Gen-Decoder-B-0
	[paragraph]
  	;you should implement this function
)

(defn Gen-Decoder-B-1
	[paragraph]
  	;you should implement this function
)

(defn Code-Breaker
	[document decoder]
  	;you should implement this function
)

;; -----------------------------------------------------
;; Test code...

(defn test_on_test_data
	[]
	(let [doc (read-as-list "document1")]
		(println doc)
	)
)


;; test code...
;(test_on_test_data)
(def filename "C:\\Users\\yldzf\\Desktop\\Programing Languages\\Homeworks\\HW1\\test.txt")
(def listem (read-as-list filename))
(count listem)

(loop [x 0]
  (when (not= x (count listem))
  (println (nth listem x))
  (println (apply str (nth listem x))) ;stringe cevirir

  (recur (inc x))))


(dec 5)
(spell-checker-0 "arisings")



(defn Example [] (
   if ( and (= 2 2) (= 3 3))
   (println "Values are equal")
   (println "Values are not equal")))
(Example)

(defn Example2 [] (

if (= (apply str (nth listem 0)) "bi")
(print "sss")
(print "aaa")))

(Example2)






(spell-checker-1 "arisings")







(defn permutations [s]
  (lazy-seq
   (if (seq (rest s))
     (apply concat (for [x s]
                     (map #(cons x %) (permutations (remove #{x} s)))))
     [s])))

(def listeee '(c b a))
(def realAlphabet '(a b c))
(def mapp (zipmap realAlphabet listeee )) ;önce value sonra key yazılır clojure mapte.
(permutations listeee)
(def perms (permutations '(a	b	c	d	e	f	g	h	i	j	k	l	m	n	o	p	q	r	s	t	u	v	w	x	y	z)))
(count perms)
(println mapp)

(println (get mapp 'c))
(println (keys mapp))
(println (vals mapp))



(def omg '(c b a))
(nth omg 1)

(defn deneme
	[spell]
(let [a (nth omg 0)
      b (nth omg 1)
      c (nth omg 2)] spell)

)
(symbol "a")
(nth omg 0)
(deneme (nth omg 0))


(require '[clojure.string :as str])
(def charseq (map str (seq "abc")))

(count charseq)
(println charseq)

;encoded-word -> decoded-word
(defn decode-word [word keyss]
  (def list '())
  (def realAlphabet '(a b c d e))
  (def decode_map (zipmap realAlphabet keyss )) ;önce value sonra key yazılır clojure mapte.

  (def charseq (map str (seq word)))
  (loop [i 0]
      (when (not= i (count charseq))
         ;(println (nth charseq i))
         ;(println (get decode_map (symbol(nth charseq i))))
         (def list (conj list (get decode_map (symbol(nth charseq i)))))
         (recur (inc i))))
  (apply str (reverse list))

)

(nth charseq 0)
(get mapp (symbol(nth charseq 0)))

(decode-word "abc" mapp)

;alfabedeki tüm kombinasyonları oluşturur ve sırasıyla o kombinasyonları sozlukte arar (her kelime için) ve en uygun
;eşleşme için alfabeyi çözer
(defn decode1 [paragraph]
  (def cur_word_count 0) ;current word in paragraph
  (def perms (permutations '(a b c d e)))

  (loop [i 0]
      (when (not= i (count perms))
         (println (nth perms i))
         (if (spell-checker-1 (decode-word (apply str (nth paragraph cur_word_count)) (nth perms i)))
           ;map current-kelime ile eşleştiyse
           (do
             (println "kelime var")
             (if (<= (count paragraph) cur_word_count)
                 (do
                   (println (str "kardesim senn alfabe: " (nth perms i)))
                   (true? true) ;bitti decode map bulundu
                    )
                 )
               (def cur_word_count (inc cur_word_count)) ;current word in paragraph

             (if (<= (count paragraph) cur_word_count)
                 (do
                   (println (str "kardesim senn alfabe: " (nth perms i)))
                   (true? true) ;bitti decode map bulundu
                    )
                 )
               (while (and (spell-checker-1 (decode-word (apply str (nth paragraph cur_word_count)) (nth perms i))) (> (count paragraph) cur_word_count))

                 (do
                 (println (str "ins sonsuz degıldır bu" cur_word_count))
                 (println (str "parag count:" (count paragraph)))

                 (def cur_word_count (inc cur_word_count))
                              (if (<= (count paragraph) cur_word_count)
                 (do
                   (println (str "kardesim senn alfabe: " (nth perms i)))
                   (true? true) ;bitti decode map bulundu
                    )
                 )
                )
               )
               (if (= (count paragraph) cur_word_count)
                  (do
                   (true? true) ;bitti decode map bulundu
                    (println (str "kardesim senn alfabe: " (nth perms i)))
                    )
                 (do
                   (def cur_word_count 0)
                   (println "kelime yok tekrar cağırıyorum bir sonraki permütasyon ile .")
                   (recur (inc i))

                   );diğer kelimerler ile eşleşmeyen map bulunmuş, yeni map aranmalı(tüm kelimelr için en baştan).
               )

             )
             ;map current-kelime ile eşleşmediyse
             (do
               (println "kelime yok tekrar cağırıyorum bir sonraki permütasyon ile last")
                (def cur_word_count 0)
                   (recur (inc i))
               )

         )))

)

(def filename "C:\\Users\\yldzf\\Desktop\\Programing Languages\\Homeworks\\HW1\\test.txt")
(def paragraph (read-as-list filename))
(decode1 paragraph)
(def perms (permutations '(a b c d e)))
(apply str (nth paragraph 0))
(nth perms 0)
(decode-word (apply str (nth paragraph 0)) (nth perms 4))


(def charseq (map str (seq (apply str (nth paragraph 0)))))
charseq
(def mapp2 (zipmap realAlphabet (nth perms 0) )) ;önce value sonra key yazılır clojure mapte.
(symbol(nth charseq 0))
(println (get mapp2 (symbol(nth charseq 0))))

perms

(decode1)
(type (nth charseq 1))
(println "asdaa")
(loop [i 0]
(when (not= i  (count charseq))
   (println (decode-word (nth charseq i)))
   (recur (inc i))))



(defn decode-word [word keyss]
  (def list '())
  (def realAlphabet '(a b c d e))
  (def decode_map (zipmap  keyss realAlphabet)) ;önce value sonra key yazılır clojure mapte.
  (println decode_map)
  (def charseq (map str (seq word)))
  (loop [i 0]
      (when (not= i (count charseq))
         (println (str "--" (nth charseq i)))
         (println (get decode_map (symbol(nth charseq i))))
         (def list (conj list (get decode_map (symbol(nth charseq i)))))
         (recur (inc i))))
  (apply str (reverse list))

)


(decode-word "abc" '(e c b a d))

(contains? #{"a" "b" "c" "d" "e"}  "a")
(first '[a b c d e])
(str (symbol "a"))











;returning function



(defn t1 [a] (str a))
(defn t2[] t1)
(t1 "deneme")
((t2) "denemeee")


(defn gen-dec-a [paragraph] (decode-word word '(a b c d e)))




