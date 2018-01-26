(defn read-as-list
	[filename]
    (try
    (catch Exception e (println (str "caught exception: " (.getMessage e)))))

    (let [words (clojure.string/split (clojure.string/trim (slurp filename)) #"\s+")]
        (map #(map (comp symbol str) %) words)))


;operators
(def OP_PLUS 43)
(def OP_MINUS 45)
(def OP_NAIL 39) ; ' operatoru list icin '()
(def OP_SLASH 47)
(def OP_ASTERISK 42)
(def OP_LEFT_PARENTHESIS 40 )
(def OP_RIGHT_PARENTHESIS 41)

;keywords
(def KW_AND "and")
(def KW_OR "or")
(def KW_NOT "not")
(def KW_EQUAL "equal")
(def KW_APPEND "append")
(def KW_CONCAT "concat")
(def KW_SET "set")
(def KW_DEFFUN "deffun")
(def KW_FOR "for")
(def KW_WHILE "while")
(def KW_IF "if")
(def KW_ELSE "else")
(def KW_THEN "then")
(def KW_TRUE "true")
(def KW_FALSE "false")
(def KW_NULL "null")

;tokenlerin tutulacaklari listeler
(def operators_list (atom '()))
(def keywords_list (atom '()))
(def identify_list (atom '()))
(def tokens_map (atom {}))
(def all_tokens (atom '())) ;tum tokenlerin tutulacagi liste


(def DEBUG false)

;verilen characterin digit olup olmadigini check eder/
(defn is_digit [character]
	(and (>= (- (int character) 48) 0) (<= (- (int character) 48) 9)))

;verilen tokenin operator olup olmadigini kontrol eder.
(defn is_token_operator [token]

  (cond
    (= (int token) OP_PLUS) "PLUS"
    (= (int token) OP_MINUS) "MINUS"
    (= (int token) OP_NAIL) "NAIL"
    (= (int token) OP_RIGHT_PARENTHESIS) "RIGHT_PARENTHESIS"
    (= (int token) OP_LEFT_PARENTHESIS) "LEFT_PARENTHESIS"
    (= (int token) OP_ASTERISK) "MULT"
    (= (int token) OP_SLASH) "SLASH"
    :else (true? false)
  )

)

;i: verilen token stringinin kontrole baslanacagi adres ( ornegin token '(23' olabilir bunun '(' ifadesini once isleriz Lexer fonksiyonunda
; kalan '23' u ise burada isleriz bunuda esleyebilmek isin token:'(23' i:1 olarak verilir.) 
;Tokenin number olup olmadigini check eder. Bunun icin bazi sartlar vardir
; negatif sayilarinda degerlendirilmesi acisindan '-' ifadesi ilk bu fonksiyonda degerlendirilir, eger yaninda sayi yoksa operatordur.
; sayi varsa\ yada hic negatif number olmadan sadece sayi varsa bu bir int numberder ve token listemize eklenir/
(defn is_token_number [i token]
    (if DEBUG (do print "IN_NUMBER_FUC i ve token:"
    (println (str i token))))
    (def nums_list (atom '()))
    (reset! nums_list (conj @nums_list (nth token i)))
    (def m i)
    (def flag (atom true))
    (cond
        ; - (45 asciide '-') geldi ve -'nin ardindaki sayi degilse operatordur, geri veriyoruz  i'yi token sayısı yapmamızın nedeni, alttaki loopa girmesini engellemek
        ( and (= (int (nth token m)) 45) (or (= (count token) (+ i 1)) (not (is_digit (nth token (+ m 1)))))) (do  (def m (count token))
                	(reset! operators_list (conj @operators_list "-" ))  (reset! all_tokens (conj @all_tokens {"-" "OPERATORMINUS"}))
    					(reset! flag false) (if DEBUG (println "is_token_num icinde - operatoru")))
    )

    (def m (+ m 1))
    (def k (atom m))
    (while (< @k (count token))


        (cond
          (is_digit(nth token @k)) (do (reset! nums_list (conj @nums_list (-(int (nth token @k)) 48)))  )
          (= (int (nth token @k))  OP_RIGHT_PARENTHESIS) (reset! k (count token))
          :else (throw (Exception. (str "Invalid Token Exception:" token)))
		)

        (reset! k (+ @k 1))

    )
    (if DEBUG (do (println (str "NUMLİST COUNT:", (count @nums_list)))
      (println (str "NUMLİST:",  @nums_list))))

    (cond

       (and @flag (not= (count @nums_list) 0)) (do (reset! nums_list (reverse @nums_list )) (reset! all_tokens (conj @all_tokens {(Integer/parseInt (apply str @nums_list)) "INT_NUM"})))

    )

    (- (count @nums_list) 1)
)


; gelen tokenin keyword olup olmadigini check eder
(defn is_token_keyword [token]

  (cond

    (or (= token KW_CONCAT ) (or (= token KW_APPEND)(or (= token KW_DEFFUN )(or (= token KW_EQUAL) (or (= token KW_NULL) (or (= token KW_THEN ) (or (= token KW_IF) (or (= token KW_ELSE ) (or (= token KW_SET ) (or (= token KW_NOT ) (or (= token KW_FOR ) (or (= token KW_WHILE) (or (= token KW_AND) (= token KW_OR))))))))))))))
      token
    :else (true? false)

  )

)
;is the given characher letter or not
(defn isLetter [character]

	(or (and (>=(int character) 65) (<=(int character)  90)) (and (>= (int character) 97) (<= (int character) 122)))

)

;gelen tokenin tum elemanlarinin [a..zA..Z] araliginda olup olmadigina bakar, eger degilse exception fırlatır
;eger hepsi kurala uyuyorsa, once keyword olup olmadiklarina bakilir, eger keyword degillerse, binary value olup olmadıklarina
;bakilir eger binary value de degilse identifier'dir.
(defn is_token_word [i token]
	(if DEBUG (do (print "is_token_word function i,token:") (println (str i token))))
    (def t_list (atom '()))
    (def indexx (atom (- i 1)))

    (def k (atom i))
    (while (< @k (count token))
		(cond
			;okunan karakter letter oldugu surece karakteri listeye ekler.
			( isLetter (nth token @k))  (do  (reset! t_list (conj @t_list (nth token @k))) (reset! indexx (+ @indexx 1))  )                ;harf ise okunan character
			; ')' okunursa word'un bittiği alamına gelir bu ve dongu break yapılır.
			(= (int  (nth token @k))  OP_RIGHT_PARENTHESIS)   (do (reset! k (count token))  )  ; break yapmak icin dongu kosulunu verdik
			:else  (throw (Exception. (str "Invalid Token Exception:" token)))

		)
        (reset! k (+ @k 1))

    )
    (reset! t_list (reverse @t_list))
    (if DEBUG (do (println (str "is_token_word token:" (apply str @t_list)))))

    (cond
      	;keyword ise token keyword listesine ve token listesine ekle
      	(not= (is_token_keyword (apply str @t_list)) false ) (do (reset! keywords_list (conj @keywords_list (is_token_keyword (apply str @t_list)) )) (reset! all_tokens (conj @all_tokens {(is_token_keyword (apply str @t_list)) "KEYWORD"}))
                                                 (if DEBUG (do (println (str "is_token_word token=keyword:" (is_token_keyword (apply str @t_list)))))) )
      	;binary value check
      	(or ( = (apply str @t_list) "true") (= (apply str @t_list) "false")) (do (reset! all_tokens (conj @all_tokens {(apply str @t_list) "BINARYVALUE"}))
                                                 (if DEBUG (do (println (str "is_token_word token=binary_value:" (apply str @t_list))))))
      	;keyword veya binary value degilse identifierdir.
      	:else (do  (reset! identify_list (conj @identify_list (apply str @t_list) )) (reset! all_tokens (conj @all_tokens {(apply str @t_list) "IDENTIFY"})) 
                  (if DEBUG (do (println (str "is_token_word token=identfier:" (apply str @t_list))))))


    )
    ;bu fonksiyoun isi bittikten sonra kalinan yerden devam edebilmek icin token'in indexi return edilir.
    @indexx

)
;Lexer, once tum dosyadaki verileri ayri ayri iceren bir liste elde eder ardindan, veriler uzerinde char char ilerler,
;bu verinin ilk karakterini inceler, bu karakter letter ise "is_token_word" fonksiyonu cagirilarak, tum verinin [a..zA..Z] araliginda olup olmadigi kontrol edilir. Ardindan uygunsa token listesine ekler.
;bu karakter digit veya '-' ise negatif bir sayi olma durumunu, pozitif bir sayi olma durumunu inceler ve uygunsa token listesine ekler.
;bu karakter operator ise token listesine ekler.
;bu durumlar disinda baska bir durum olusursa exception olusturur.
(defn Lexer [filename]

	(def listem (read-as-list filename))


    (loop [i 0] ;tokens
	    (when (< i (count listem))
	      (def token (apply str (nth listem i)))
	      (if DEBUG (do (print token) (println (str " count:" (count token)))))

	      	(def j (atom 0))

	      	(while (< @j (count token));bir token içinde gezim
	          	(do

		              (if DEBUG (do (println (str "okunan char:" (nth token @j)))))

		              (cond
		              	;word kontrol (keyword-identifier-binary)
		                ( isLetter (nth token @j)) (do (try  (reset! j (is_token_word @j token) )    (catch Exception e (throw e)))
		                                                                                                  (if DEBUG (do (println "Lexer_okunan char_is_letter" )))   )

		                ;number control
		                (or (is_digit (nth token @j)) (= (int(nth token @j)) OP_MINUS)) (do (try  (reset! j (+ (is_token_number @j token) @j))     (catch Exception e (throw e)))
		                                            (if DEBUG (do (println  "Lexer_okunan char_is_number" )))   )

		                ;operator control
		                (not= (is_token_operator (nth token @j)) false) (do

		                	(reset! operators_list (conj @operators_list (nth token @j) )) (reset! all_tokens (conj @all_tokens {(nth token @j) (str "OPERATOR" (is_token_operator (nth token @j))  )}))
		                                                                  (if DEBUG (do (println  "Lexer_okunan char_is_operator" )))   )


						:else (throw (Exception. "Unsolved Token Exception"))

		              )
		              (reset! j (+ @j 1))

	          	)

	      	)
	      (recur(inc i))
	    )

	)
	;Listeye son eklenilenler basa eklendigi icin liste reverse edilmeli
	(reset! all_tokens (reverse @all_tokens))

)
;test function
(defn main []
	(try
		(println (Lexer "CoffeeSample.coffee"))
		(catch Exception e (println (str "caught exception: " (.getMessage e))))
	)
)

(main)