*This project has been created as part of the 42 curriculum by tfujikaw.*

# Description（説明）

## プロジェクトの目的
このプロジェクトの目的は、標準関数を自分自身で実装し、それらを効果的に使う方法を学ぶことで、関数がどのように機能しているのかを理解することにあります。

## プロジェクト概要
- part1 : C言語の標準関数の再実装。
- part2 : libcに含まれていない、あるいは異なる形で存在する関数の開発。
- part3 : 連結リスト関連の関数を開発。

# Instructions (手順)

- 1. ターミナル内で make コマンドを実行し、静的ライブラリ(libft.a)を作成。
- 2. 作成した libft.a と libft.h を自分のソースコードと同じディレクトリに配置し、以下のようにコンパイルします。
例 : cc main.c -L. -lft
各オプションの説明
部分意味cc : Cコンパイラ
main.c : コンパイルするソースファイル
-L. : ライブラリの検索パスに .（カレントディレクトリ） を追加
-lft : libft というライブラリをリンクする

.oファイル = オブジェクトファイルを作成することにより
大規模な開発する際に分割コンパイルによるビルドの高速化、複数人での開発や再利用がしやすいモジュール化が可能。

以下C言語のソースコードが実行可能ファイルになるまでの流れ
https://daeudaeu.com/exe/#i-3

# Resources
- AIについて
課題文の翻訳、完成したファイルの最終確認及びテストに使用。
連結リスト等、腹落ちしてない部分の確認等に使用。
ピアラーニングを最優先とし、AIは最終手段として使用しました。

## Makefileについて
- 静的ライブラリの採用 : 複数のオブジェクトファイルを一つにまとめることで、他のプロジェクトへの持ち運びとリンクを容易にしています。

- make : ソースファイルをコンパイルし、静的ライブラリ libft.a を作成します。

- make clean	: コンパイル時に生成されたオブジェクトファイル（.o）を削除します。

- make fclean	: clean に加え、生成されたライブラリ本体（libft.a）も削除します。

- make re	: fclean を実行した後、再度 make を行い、完全に再ビルドします。

- パターンルールと自動変数 : %.o: %.cのルールにより、変更があったファイルだけを再コンパイル（分割コンパイル）するように設計し、ビルド時間を短縮しています。

- CFLAG   = -Wall -Wextra -Werror : 42の規約に基づき、すべての警告をエラーとして扱う厳格なコンパイルオプションを設定しています。

- .PHONY : ターゲット名と同じ名前のファイルがディレクトリ内に存在しても、 Makefile のコマンドが正しく実行されるようにしています

# 各関数の説明、Resources
## part 1

- isalpha
文字cをチェックして英字であるかを判定する。
https://cgengo.sakura.ne.jp/isalpha.html
https://bituse.info/c_func/20

- isdigit
文字cをチェックして数値であるかを判定する。
http://www.cgengo.sakura.ne.jp/isdigit.html

- isalnum
文字が英字または数字であるかどうか判定する。
http://www.cgengo.sakura.ne.jp/isalnum.html

- isascii
文字がASCII文字か判定。
https://nxmnpg.lemoda.net/ja/3/isascii

- isprint
文字が表示可能であるかどうか判定する。
https://nxmnpg.lemoda.net/ja/3/isprint

- strlen
文字列の長さを求める。
https://cgengo.sakura.ne.jp/strlen.html
https://paiza.jp/works/reference/article-c-strlen

- memset
メモリ領域を指定する文字で埋める。
https://cgengo.sakura.ne.jp/memset.html
https://www.ibm.com/docs/ja/i/7.5.0?topic=functions-memset-set-bytes-value

- bzero
バイト列 s から始まる領域の先頭 n バイトを 数値ゼロ (値が '\0' のバイト) で埋める。
https://www.ibm.com/docs/ja/zos/2.5.0?topic=functions-bzero-zero-bytes-in-memory
https://linuxjm.sourceforge.io/html/LDP_man-pages/man3/bzero.3.html

- memcpy
メモリ領域をコピーする
https://ninjacode.work/magazine/programming/【c言語入門】memcpy関数の使い方と注意点/
https://nxmnpg.lemoda.net/ja/3/memcpy
https://linuxjm.sourceforge.io/html/LDP_man-pages/man3/memcpy.3.html

- memmove
メモリ領域srcの先頭からnバイトをメモリ領域destに上書きする関数。
memcpy()と機能は同じであるが、memmove()はコピー元のメモリ領域とコピー先のメモリ領域が重なっても問題ない。
https://cgengo.sakura.ne.jp/memmove.html
https://bituse.info/c_func/57

- strrchr
strrchr() 関数は、文字列 s 中の (char に変換された) c が最後に出現する位置を探します。
https://nxmnpg.lemoda.net/ja/3/strrchr

- strncmp
2つの文字列s1, s2の先頭からnumバイトまでを比較する。
https://www.sejuku.net/blog/25303
https://cgengo.sakura.ne.jp/strncmp.html

- strlcpy
文字列を安全にコピーするための関数。
https://taidanahibi.com/c/strcpy-strncpy-strlcpy/#index_id2
https://www.wdic.org/w/TECH/strlcpy
https://ja.wikipedia.org/wiki/Strlcpy

- strlcat
文字列を安全に結合する関数。
https://qiita.com/aho17/items/148f4dd361bc85b0725f
https://www.koeki-prj.org/roy/~yuuji/2021/pe/11/strop.html

- memchr
関数は、ポインター s が指し示すメモリー領域の先頭の n バイトから最初に登場する文字 c を探す。 
c と s が指し示すメモリー領域の各バイトは両方とも unsigned char と解釈される。
https://linuxjm.sourceforge.io/html/LDP_man-pages/man3/memchr.3.html
https://zenn.dev/tecchan/articles/d8932c516c322f

- memcmp
指定バイト数のメモリブロックを比較する関数。
https://www.ibm.com/docs/ja/i/7.4.0?topic=functions-memcmp-compare-buffers
https://bituse.info/c_func/55

- toupper
引数が大文字に変換できる文字であれば大文字に変換する。
https://cgengo.sakura.ne.jp/toupper.html

- tolower
引数が小文字に変換できる文字であれば小文字に変換する。
https://cgengo.sakura.ne.jp/tolower.html

- strnstr
検索された len 文字より少ない文字列 big の中で、 ヌル文字で終了する文字列 little が最初に出現する位置を探します。 
‘\0’ の後に現れる文字は、検索されません。
https://nxmnpg.lemoda.net/ja/3/strstr

- strchr
文字strの中から文字cがあるかどうか探索する。
対象の文字が見つかった場合、最初に現れた文字cのポインタを返す。
https://cgengo.sakura.ne.jp/strchr.html
https://linuxjm.sourceforge.io/html/LDP_man-pages/man3/strchr.3.html
https://nxmnpg.lemoda.net/ja/3/strchr

- atoi
文字列を整数型に変換する。
https://linuxjm.sourceforge.io/html/LDP_man-pages/man3/atoi.3.html

- calloc
calloc関数は、C言語でメモリを動的に確保するための標準ライブラリ関数です。
mallocと似ていますが、確保したメモリ領域を自動的にゼロで初期化してくれる特徴があります。
https://paiza.jp/works/reference/article-c-calloc

- strdup
文字列を動的にコピー（複製）する関数。
https://www.ibm.com/docs/ja/i/7.6.0?topic=functions-strdup-duplicate-string
https://nxmnpg.lemoda.net/ja/3/strdup#google_vignette

## part2

- ft_substr
malloc(3) を使用してメモリを確保し、文字列 's' からサブ文字列を返します。
サブ文字列はインデックス 'start' から始まり、最大長さは 'len' です。

- ft_strjoin
malloc(3) を使用してメモリを確保し、's1' と 's2' を連結した結果である新しい文字列を返します。

- ft_strtrim
malloc(3) を使用してメモリを確保し、's1' の前方と後方から 'set' に含まれる文字を取り除いたコピーを返します。

- ft_split
malloc(3) を使用してメモリを確保し、文字列 's' を区切り文字 'c' で分割して得られる文字列の配列を返します。配列内の各文字列は個別にメモリ確保されます。ポインタの配列自体も動的にメモリ確保されます。配列の最後は NULL で終わらなければなりません。

- ft_itoa
malloc(3) を使用してメモリを確保し、引数として受け取った整数を表す文字列を返します。負の数も処理する必要があります。

- ft_strmapi
文字列 's' の各文字に関数 'f' を適用します。その際、'f' の第1引数にはインデックス（文字の位置）、第2引数にはその文字自体を渡します。連続して適用した結果を格納するための新しい文字列を（malloc(3) を使用して）作成し、返します。

- ft_striteri
引数として渡された文字列 's' の各文字に関数 'f' を適用します。その際、'f' の第1引数にはインデックスを渡し、第2引数にはその文字の「アドレス」を渡します。各文字はアドレス（ポインタ）経由で 'f' に渡されるため、必要に応じて元の文字列を直接修正することが可能です。

### ファイルディスクリプタとは
https://qiita.com/FR1SK_noob/items/873d3820ebf869a32d5e

- ft_putchar_fd
指定されたファイル記述子に対して、文字 'c' を出力します。

- ft_putstr_fd
指定されたファイル記述子に対して、文字列 's' を出力します。

- ft_putendl_fd
指定されたファイル記述子に対して、文字列 's' を出力し、続けて改行を出力します。

- ft_putnbr_fd
指定されたファイル記述子に対して、整数 'n' を出力します。

## part 3
- 連結リストについて
https://www.youtube.com/watch?v=RBd0vEO6j2M&t=338s
https://www.youtube.com/watch?v=93uVys5N3_Q

- ft_lstnew
malloc(3) を使用してメモリを確保し、新しいノードを返します。メンバ変数 'content' は引数として渡された 'content' で初期化されます。変数 'next' は NULL で初期化されます。

- ft_lstadd_front
リストの先頭にノード 'new' を追加します。

- ft_lstsize
リスト内のノードの数をカウントします。

- ft_lstlast
リストの最後のノードを返します。

- ft_lstadd_back
リストの末尾にノード 'new' を追加します。

- ft_lstdelone
引数として受け取ったノードに対し、関数 'del' を使ってそのコンテンツ（content）を解放します。その後、ノード自体も解放します。ただし、次のノード（next）は解放してはいけません。

- ft_lstclear
指定されたノード、およびそれ以降のすべての後続ノードを、関数 'del' と free(3) を使って削除・解放します。最後に、リストのポインタを NULL に設定します。

- ft_lstiter
リスト 'lst' を最初から辿り、各ノードのコンテンツに対して関数 'f' を適用します。

- ft_lstmap
リスト 'lst' を最初から辿り、各ノードのコンテンツに対して関数 'f' を適用します。その適用結果（戻り値）をコンテンツに持つ新しいノードを作成し、それらを繋げた新しいリストを返します。途中でメモリ確保に失敗した場合などは、関数 'del' を使ってそれまでに作成したノードを適切に解放する必要があります。
