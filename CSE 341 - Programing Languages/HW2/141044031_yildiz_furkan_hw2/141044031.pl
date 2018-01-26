%141044031 Furkan YILDIZ

%%%%%%%%%%%%%%% PART 1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%
flight(istanbul,izmir,3).
flight(istanbul,ankara,5).
flight(istanbul,trabzon,3).
flight(izmir,antalya,1).
flight(izmir,ankara,6).
flight(trabzon,ankara,2).
flight(ankara,konya,8).
flight(konya,diyarbakir,1).
flight(antalya,diyarbakir,5).
flight(konya,kars,5).
flight(kars,gaziantep,3).
flight(edirne,edremit,5).
flight(edremit,erzincan,7).


flight(izmir,istanbul,3).
flight(ankara,istanbul,5).
flight(trabzon,istanbul,3).
flight(antalya,izmir,1).
flight(ankara,izmir,6).
flight(ankara,trabzon,2).
flight(konya,ankara,8).
flight(diyarbakir,konya,1).
flight(diyarbakir,antalya,5).
flight(kars,konya,5).
flight(gaziantep,kars,3).
flight(edremit,edirne,5).
flight(erzincan,edremit,7).


%DFS gibi calismasada DFS mantigina benzer bir algorithma ile yazıldı kurallar. Bu algorithmaya gore, visited listesi ve 
%gezilen komsuların eklendigi rota listesi bulunmakta. 

%baslangic sehri hemen visited listesine ekleniyorken go kuralı cagiriliyor, bu kuralla gore, baslangic sehrinden herhangi,
%sehre ucus gerceklestiriliyor ve bu sehire gitmek icin katedilen rotanın visited listesinde olup olmadıgı kontrol ediliyor, 
%eger varsa o rota üzerinden o sehre gidilmistir ve tekrar gidilmesine gerek yoktur, eger bu engellenmezse sonsuza girer sorgular
%eger yoksa o rota tekrar ugramamak icin visited listesine eklenir ardından o sehirden baska bir sehire ardından baska bir
%sehire ta ki tum rotalar ziyaret edilene kadar gezilebilmesi icin recursion olarak ana fonksiyonumuzu cagiriyoruz.
%Ana fonksiyonumuzu cagirirken ise visited listesine yeni rotamizi ekliyoruz.
%Recursion'un base case'si ise rotaya en son eleman eklenmeden once rota ile visited listesinin aynı olmasıdır, en son elamanda
%eklendikten sonra backtracking ile islemler yapılıyor.
%Bu sekilde graph'taki tum pathler yanlız bir kere gezilmis oluyor.

route(X,Y,C) :- go(X,Y,_,[X],C).
go(X,Y,[Y|ROUTE],ROUTE,C) :-  flight(X,Y,C).
go(X,Y,ROUTE,VISITED,C) :- flight(X,Z,A), \+ contains(VISITED,Z),go(Z,Y,ROUTE,[Z|VISITED],B),C is A + B.



%%%%%%%%%%%%%%% PART 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%


%LISTEDEN 2 SERLI 2 SERLI ELEMAN CIKARTILARAK, 2 ELEMAN KARSILASTIRILIYOR BUYUK OLAN LISTEDEN ATILARAK DEVAM EDILIYOR,
%BU DURUMDA EN SONA KALAN LISTENIN MINIMUM NUMBERI OLACAKTIR.
find_min_of_list([MINIMUM],MINIMUM).  
find_min_of_list([L1,L2|T],M) :- L1 =< L2, find_min_of_list([L1|T],M).
find_min_of_list([L1,L2|T],M) :- L1 > L2, find_min_of_list([L2|T],M). 

%TUM ROTALARI CIKARTIP BU ROTALARIN COST LISTESINI OLUSTURUYORUZ ARDINDAN BU LISTEDEKI MINIMUM SAYIYI GONDERIYORUZ.
croute(X,Y,R) :-  findall(C0, route(X, Y,C0), COSTLIST),find_min_of_list(COSTLIST,R).


%%%%%%%%%%%%%%% PART 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%

enrolment(1,a).
enrolment(1,b).
enrolment(2,a).
enrolment(3,b).
enrolment(4,c).
enrolment(5,d).
enrolment(6,d).
enrolment(6,a).

enrolment(7,a).
enrolment(7,b).

enrolment(8,a).
enrolment(8,b).

enrolment(9,a).
enrolment(9,b).

enrolment(10,g).
enrolment(10,b).

enrolment(11,a).
enrolment(11,f).

when(a,10).
when(b,12).
when(c,11).
when(d,16).
when(e,17).
when(f,15).
when(g,18).

where(a,101).
where(b,104).
where(c,102).
where(d,103).
where(e,103).
where(f,101).
where(g,103).

schedule(S,P,T) :- enrolment(S,ST) , where(ST,P) , when(ST,T).
usage(P,T) :- where(ST, P) , when(ST, T).
%t 'de baslayan konferans ile t+2 'ye kadar baslayan konferanslar aynı odada iseler cakistiklari, 
%t+2 ve sonrasinda ise cakismadiklari kabul edildi. Yani konferaslar aralarindaki saatlerin cakisması icin 
%+2 -2 aralıgında +2 -2 dahil olmamak uzere kabul edildi.
conflict(X,Y) :- where(X,P1) , where(Y,P2) ,when(X,T1) , when(Y,T2),abs(T1-T2) < 2, =(P1,P2). 
meet(X,Y) :- enrolment(X,C1),enrolment(Y,C2), when(C1,T1) , when(C2,T2) , where(C1,P1) , where(C2,P2) , abs(T1-T2) < 2, =(P1,P2).



%%%%%%%%%%%%%%% PART 4 %%%%%%%%%%%%%%%%%%%%%%%

%birinci listedeki elemanları tek tek cikartarak, eger cikartilan eleman ikinci listede yoksa, I listesine ekliyor ta ki
%birinci liste bosalana kadar, bosaldıgında ise, ikinci listeyi I ya aynen atıyor ve backtracking ile  I = L2 + L1/L2 oluyor.
union([],L,L).
union([H | T], L2, I) :- contains(L2, H),!, union(T,L2, I).
union([H | T], L2, [H | I]) :- union(T, L2,I).

%birinci listedeki elemanları tek tek cikartarak, eger cikartilan eleman ikinci listedede varsa, I listesine ekliyor ta ki
%birinci liste bosalana kadar, bosaldıgında ise I listesinide bos listeye cevirir ve backtracking ile kesisim elemanlarını ekler.
intersect([],_,[]).
intersect([H|T], L2, [H | I]) :- contains(L2, H),!, intersect(T,L2,I).
intersect([_|T], L2,I) :- intersect(T,L2,I).

%verilen listedeki elemanları tek tek cikartarak liste bosalana kadar, aranan elemana esit bir eleman olup olmadıgını kontrol eder.
contains([H|_], H).
contains([_|T], Y) :- contains(T,Y).

%birinci listedeki elemanları tek tek cikartarak, ikinci listeye ekler, ta ki birinci liste bosalana kadar, bosaldıgında ise
%ikinci listeyi, result listesine atar ardından backtracking ile result listesi L1+L2 olur.
concatLists([],L,L).
concatLists([HL1 | TL1] ,L2, [HL1 | L3]) :- concatLists(TL1,L2,L3).

%Recursion listenin ilk elemanıyla ve sonrasıyla ayrı ayrı ilgileniyor, eleman liste degilse listeye çeviriyor ta ki liste
%bosalana kadar, bosaldıgında ise tek yapilmasi gereken, 2 listeyi merge etmek.
flatten([],[]) :- !. %Liste bosaldıgında return true, backtrack icin.
flatten([H|T], F) :- !,flatten(H, FH), flatten(T, FT), concatLists(FH, FT, F). 
flatten(L, [L]).