#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;math.h&gt;
#define TRUE 1
#define FALSE 0
#define DATA_SIZE0 2
#define DATA_SIZE DATA_SIZE0*DATA_SIZE0
/************************************************************************
問題 (答え) の表示
************************************************************************/
void print_board(int board[DATA_SIZE][DATA_SIZE]){
int x,y;
/* 問題 (答え) (board[y][x]) を表示する。
数字がまだ決まっていないところには - を表示する。
&lt;表示例&gt;
- - 1 - 8 7 - 5 -
- 5 - - 3 - - 8 -
- - - - - 9 - - 3
3 - - - - - 6 - -
6 4 - - - - - 7 2
- - 5 - - - - - 9
7 - - 1 - - - - -
- 1 - - 7 - - 2 -
- 9 - 8 6 - 5 - - */
/*** この部分を自分で書く ***/
for(y=0;y&lt;DATA_SIZE;y++){
for(x=0;x&lt;DATA_SIZE;x++){
if(board[y][x]==0){
printf(&quot;- &quot;);
}else{

printf(&quot;%d &quot;, board[y][x]);
}
}
printf(&quot;\n&quot;);
}
}

/************************************************************************
問題データの読み込み
************************************************************************/
void read_problem(char *fname, int board[DATA_SIZE][DATA_SIZE]){
int x, y;
FILE *fp;
if((fp=fopen(fname,&quot;r&quot;))==NULL){
printf(&quot;read_problem(): Cannot open \&quot;%s\&quot;\n&quot;,fname);
exit(1);
}
for(y=0;y&lt;DATA_SIZE;y++){
for(x=0;x&lt;DATA_SIZE;x++){
fscanf(fp,&quot;%d &quot;,&amp;board[y][x]);
}
}
fclose(fp);
}
/************************************************************************
空白マスの検出
board[*y][*x]から順番にチェックしていき、
空白マス(0が入っているところ)があれば TRUE を返す
(x,y)が空白マス
なければ FALSE を返す
************************************************************************/
int find_blank(int *x, int *y, int board[DATA_SIZE][DATA_SIZE]){
int i,j;
for(;*y&lt;DATA_SIZE;(*y)++,*x=0){
for(;*x&lt;DATA_SIZE;(*x)++){
/* board[*y][*x]が0ならば TRUE を返す */
/*** この部分を自分で書く ***/
if(board[*y][*x]==0){

return TRUE;
}
}
}
return FALSE;
}
/************************************************************************
問題を解く
************************************************************************/
void solve(int x, int y, int board[DATA_SIZE][DATA_SIZE])
{
int i,j,x0,y0;
int possible[DATA_SIZE+1]; /* 1〜9のうちどの数字が使えるか */
/* 途中経過を表示 */
// printf( &quot;[途中経過]\n&quot; );
// print_board(board);
/* 空白のマスがなければ答えを表示する */
if(!find_blank(&amp;x,&amp;y,board)){
printf( &quot;[答え]\n&quot; );
print_board(board);
return;
}
/* 全て使用可にする */
for(i=1;i&lt;=DATA_SIZE;i++){
possible[i]=TRUE;
}
/* 縦・横方向に boardの値を調べて、すでに使用されている数字のところは
possible を FALSE にする */
for(i=1;i&lt;=DATA_SIZE;i++){
/* 横方向 */
/*** この部分を自分で書く ***/
for(y0=0;y0&lt;DATA_SIZE;y0++){
if(board[y0][x] == i){
possible[i] = FALSE;
}
}
/* 縦方向 */

/*** この部分を自分で書く ***/
for(x0=0;x0&lt;DATA_SIZE;x0++){
if(board[y][x0] == i){
possible[i] = FALSE;
}
}
}
/* DATA_SIZE0xDATA_SIZE0の枠の中の board の値を調べて、
すでに使用されている数字のところは possible を FALSE にする */
/*** この部分を自分で書く ***/
//(x/DATA_SIZE0)*DATA_SIZE0
for(i=1;i&lt;=DATA_SIZE;i++){
for(y0=(y/DATA_SIZE0)*DATA_SIZE0;y0&lt;(DATA_SIZE0+(y/DATA_SIZE0)*DATA_SIZE0);y0++){
for(x0=(x/DATA_SIZE0)*DATA_SIZE0;x0&lt;(DATA_SIZE0+(x/DATA_SIZE0)*DATA_SIZE0);x0++){
if(board[y0][x0] == i){
possible[i] = FALSE;
}
}
}
}
for(i=1;i&lt;=DATA_SIZE;i++){
if(possible[i]==FALSE){
continue;
}
/* i を (x,y)に入れることができるとして探索 */
board[y][x]=i;
solve(x,y,board); /* 再帰呼び出し */
board[y][x]=0;
}
}
/************************************************************************
メインプログラム
************************************************************************/
int main( int argc, char *argv[])
{
int board[DATA_SIZE][DATA_SIZE];
if(argc!=2){
printf(&quot;使用法 : ./a.out 問題ファイル&quot;);
}

/* 問題の読み込み */
read_problem(argv[1],board);
/* 問題の表示 */
printf(&quot;[問題]\n&quot;);
print_board(board);
/* 問題を解く */
solve(0,0,board);
return 0;
}