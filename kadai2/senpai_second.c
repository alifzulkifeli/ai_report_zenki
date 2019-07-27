#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define POP_SIZE 5 /* 個体数 (必ず奇数に設定) */
#define G_LENGTH 10 /* 個体の遺伝子型のビット数 */
#define MAX_GEN 20 /* 世代数 */
#define M_RATE 0.1 /* 突然変異率 (0〜1) */
/********************************************************************
乱数の発生 (Seedの決定)
********************************************************************/
void init_rnd()
{
srand((unsigned int)time(NULL));
}
/********************************************************************
乱数の発生 (0〜1の乱数)
********************************************************************/
double Random()
{
return((double)rand()/RAND_MAX);
}
/********************************************************************
遺伝子の初期化
引数 gene[p][i] : 遺伝子pのi番目の成分
********************************************************************/
void init_gene(int gene[POP_SIZE][G_LENGTH])
{
int p,i;
/* 乱数の初期化 */
init_rnd();

/* 遺伝子を初期化 0〜1の乱数を発生し、0.5以上なら1
0.5未満なら0 */
printf(&quot;&lt;&lt; 初期個体群 &gt;&gt;\n&quot;);
/*** この部分を自分で書く ***/
for(p=0;p&lt;POP_SIZE;p++){
for(i=0;i&lt;G_LENGTH;i++){
if(Random() &lt; 0.5){
gene[p][i] = 0;
}else gene[p][i] = 1;
}
}
}
/********************************************************************
適応度の計算
引数 gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
********************************************************************/
void calc_fitness(int gene[POP_SIZE][G_LENGTH], double fitness[POP_SIZE])
{
int p,i;
/* 適応度の計算 前半の5bitは0の数 後半の5bitは1の数 */
/*** この部分を自分で書く ***/
for(p=0;p&lt;POP_SIZE;p++){
fitness[p] = 0;
for(i=0;i&lt;5;i++){
if(gene[p][i] == 0){
fitness[p] += 1;
}
}
for(; i &lt; G_LENGTH; i++){
if(gene[p][i] == 1){
fitness[p] += 1;
}
}
}
}
/**********************************************************************

遺伝子の表示 &amp; 最大適応度・平均適応度の計算 &amp; ファイルへの書き出し
引数 t : 世代数
gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
*fp : ファイルポインタ
**********************************************************************/
void show_gene(int t, int gene[POP_SIZE][G_LENGTH],
double fitness[POP_SIZE],
FILE *fp)
{
int p,i;
double avg_fit; /* 平均適応度 */
double max_fit; /* 最大適応度 */
/* 個体の値、適応度の表示 */
/*** この部分を自分で書く ***/
//individual value
printf(&quot;individual Value :\n&quot;);
for(p=0;p&lt;POP_SIZE;p++){
for(i=0;i&lt;G_LENGTH;i++){
printf(&quot;%d&quot;,gene[p][i]);
}
printf(&quot;\n&quot;);
}
printf(&quot;\n&quot;);

//fitness value
printf(&quot;Fitness Value : &quot;);
for(i =0;i&lt; POP_SIZE;i++){
printf(&quot;%f &quot;,fitness[i]);
}
printf(&quot;\n&quot;);
/* 平均・最大適応度の計算 */
/*** この部分を自分で書く ***/
for(p=0;p&lt;POP_SIZE;p++){
if(max_fit &lt; fitness[p]){
max_fit = fitness[p];
}
avg_fit += fitness[p];

}
avg_fit /= POP_SIZE;

/* 平均・最大適応度の表示 */
printf(&quot;平均適応度 : %lf\n&quot;,avg_fit);
printf(&quot;最大適応度 : %lf\n&quot;,max_fit);
/* 平均・最大適応度をファイルに書き込む */
fprintf(fp,&quot;%d %lf %lf\n&quot;,t,avg_fit,max_fit);
}
/**********************************************************************
個体番号 p1 と p2 の適応度と遺伝子を交換
引数 p1, p2 : 遺伝子の番号
gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
**********************************************************************/
void swap_gene(int p1, int p2, int gene[POP_SIZE][G_LENGTH],
double fitness[POP_SIZE] )
{
int tmp;
double f;
int i;
/* 遺伝子型の交換 (遺伝子p1と遺伝子p2の値を入れ替える) */
/*** この部分を自分で書く ***/
for(i=0;i&lt;G_LENGTH;i++){
tmp = gene[p1][i];
gene[p1][i] = gene[p2][i];
gene[p2][i] = tmp;
}

/* 適応度の交換 (遺伝子p1と遺伝子p2の適応度の値を入れ替える) */
/*** この部分を自分で書く ***/
f = fitness[p1];
fitness[p1] =fitness[p2];
fitness[p2] = f;

}
/**********************************************************************
個体番号 p1 の適応度と遺伝子型を p2 にコピー
引数 p1, p2 : 遺伝子の番号
gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
**********************************************************************/
void copy_gene(int p1, int p2, int gene[POP_SIZE][G_LENGTH],
double fitness[POP_SIZE] )
{
int i;
/* 遺伝子のコピー (遺伝子p1を遺伝子p2にコピーする) */
/*** この部分を自分で書く ***/
for(i=0;i&lt;G_LENGTH;i++){
gene[p2][i] = gene[p1][i];
}

/* 適応度のコピー (遺伝子p1の適応度を遺伝子p2の適応度にコピーする)*/
/*** この部分を自分で書く ***/
fitness[p2] = fitness[p1];
}
/**********************************************************************
エリート保存
(最小適応度の個体に最大適応度の個体のデータをコピー)
引数 gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
**********************************************************************/
void elite(int gene[POP_SIZE][G_LENGTH], double fitness[POP_SIZE])
{
int p,i;
double max_fitness=fitness[0];
double min_fitness=fitness[0];
int max_p=0;
int min_p=0;
/* 最大適応度の個体(max_p)と最小適応度の個体(min_p)を見つける */

/*** この部分を自分で書く ***/
for(p=1;p&lt;POP_SIZE;p++){
if(max_fitness &lt;= fitness[p]){
max_fitness = fitness[p];
max_p = p;
}
if(min_fitness &gt;= fitness[p]){
min_fitness = fitness[p];
min_p = p;
}
}

/* 最小適応度の個体に最大適応度の個体をコピー */
copy_gene(max_p,min_p,gene,fitness);
/* 最大適応度の個体を0番目に移動 */
swap_gene(0,max_p,gene,fitness);
}
/**********************************************************************
ルーレット選択
引数 gene[p][i] : 遺伝子pのi番目の成分
fitness[p] : 遺伝子pの適応度
**********************************************************************/
void reproduction(int gene[POP_SIZE][G_LENGTH], double fitness[POP_SIZE])
{
double sum_of_fitness; /* 個体の適応度の総和 */
double border; /* ルーレット上の個体間の境界 */
double r; /* ルーレット上の選択位置 */
int p,i; /* 選ばれた個体の番号 */
int num; /* 0 &lt;= num &lt;= POP_SIZE-1 */
int new_gene[POP_SIZE][G_LENGTH];
/* ルーレットの1周分 sum_of_fitness を求める */
sum_of_fitness = 0.0;
for(p=0;p&lt;POP_SIZE;p++){
sum_of_fitness += fitness[p];
}
/* ルーレットを POP_SIZE 回だけ回して次世代の個体を選ぶ */
for(p=1;p&lt;POP_SIZE;p++){
/* ルーレットを回して場所を選ぶ

r : 選ばれた位置 (0 &lt;= r &lt;= sum_of_fitness) */
r=sum_of_fitness*Random();
/* 選ばれた場所に該当する個体が何番か調べる
num : 選ばれた個体の番号 (0 &lt;= num &lt;= POP_SIZE-1) */

num=0;
border = fitness[0]; /* 個体間の境界 */
while(border&lt;r){
num++;
border+=fitness[num];
}

/* 遺伝子の代入 */
for(i=0;i&lt;G_LENGTH;i++){
new_gene[p][i]=gene[num][i];
}
}
/* 遺伝子のコピー */
for(p=1;p&lt;POP_SIZE;p++){
for(i=0;i&lt;G_LENGTH;i++){
gene[p][i]=new_gene[p][i];
}
}
}
/**********************************************************************
一点交叉
引数 gene[p][i] : 遺伝子pのi番目の成分
**********************************************************************/
void crossover(int gene[POP_SIZE][G_LENGTH])
{
int gene1[G_LENGTH]; /* 親1の遺伝子型 */
int gene2[G_LENGTH]; /* 親2の遺伝子型 */
int i,j;
int c_pos; /* 交叉位置 (1 &lt;= c_pos &lt;= G_LENGTH-1) */
/* 交叉位置を1〜G_LENGTH-1の範囲でランダムに決め、

それより後ろを入れ替える。
gene[1]とgene[2], gene[3]とgene[4] ... のように親にする */
/*** この部分を自分で書く ***/
c_pos = (Random()*(G_LENGTH-1)) + 1;
for(i=1;i&lt;POP_SIZE;i+=2){
for(j=c_pos;j&lt;G_LENGTH;j++){
gene1[j] = gene[i][j];
gene2[j] = gene[i+1][j];
}
for(j = c_pos;j&lt;G_LENGTH;j++){
gene[i][j] = gene2[j];
gene[i+1][j] = gene1[j];
}
}
}
/**********************************************************************
二点交叉 (余裕があれば)
引数 gene[p][i] : 遺伝子pのi番目の成分
**********************************************************************/
void two_crossover(int gene[POP_SIZE][G_LENGTH])
{
int gene1[G_LENGTH]; /* 親1の遺伝子型 */
int gene2[G_LENGTH]; /* 親2の遺伝子型 */
int p,i;
int c_pos1, c_pos2; /* 交叉位置 (1 &lt;= c_pos1,2 &lt;= G_LENGTH-1) */
int tmp;
/* 交叉位置を1〜G_LENGTH-1の範囲でランダムに2つ決め、その間を入れ替える。
gene[1]とgene[2], gene[3]とgene[4] ... のように親にする */
/*** この部分を自分で書く ***/
c_pos1=(rand() * (G_LENGTH-1)+1);
c_pos2=(rand() * (G_LENGTH-1)+1);

if(c_pos1 &gt; c_pos2){
tmp=c_pos1;
c_pos2=c_pos1;
c_pos1=tmp;
}
for(p = 1; p &lt; POP_SIZE; p += 2){
for(i = c_pos1; i &lt; c_pos2; i++){
gene1[i] = gene[p][i];
gene2[i] = gene[p+1][i];
}
for(i = c_pos1; i &lt; c_pos2; i++){
gene[p][i] = gene2[i];
gene[p+1][i] = gene1[i];
}
}
}
/**********************************************************************
突然変異
引数 gene[p][i] : 遺伝子pのi番目の成分
**********************************************************************/
void mutation(int gene[POP_SIZE][G_LENGTH])
{
int p,i;
/* 0〜1の乱数を発生させ、その値が M_RATE 以下ならば
遺伝子の値をランダムに変える (0ならば1、1ならば0) */
/*** この部分を自分で書く ***/
for(p=0;p&lt;POP_SIZE;p++)
for(i=0;i&lt;G_LENGTH;i++)
if(Random() &lt;= M_RATE)
gene[p][i] = (gene[p][i] == 1)? 0: 1;
}
/**********************************************************************
メインプログラム
**********************************************************************/
int main(int argc, char *argv[])
{
int gene[POP_SIZE][G_LENGTH];
double fitness[POP_SIZE];
int t;

FILE *fp;
/* 適応度の変化を記録するファイルのオープン */
if((fp=fopen(&quot;result.dat&quot;,&quot;w&quot;))==NULL){
printf(&quot;Cannot open \&quot;result.dat\&quot;\n&quot;);
exit(1);
}
/* シミュレーション条件の表示 */
printf(&quot;個体数 : %d\n&quot;,POP_SIZE);
printf(&quot;遺伝子長 : %d bit\n&quot;,G_LENGTH);
printf(&quot;突然変異率 : %lf\n&quot;,M_RATE);

init_gene(gene); /* 遺伝子の初期化 */
calc_fitness(gene,fitness); /* 適応度の計算 */
show_gene(0,gene,fitness,fp); /* 表示 */
for(t=1;t&lt;=MAX_GEN;t++){
printf(&quot;&lt;&lt; 世代数 : %d &gt;&gt;\n&quot;,t);
elite(gene,fitness); /* エリート保存 */
reproduction(gene,fitness); /* ルーレット選択 */
crossover(gene); /* 単純交叉 */
//two_crossover(gene); /* 二点交叉 */
mutation(gene); /* 突然変異 */
calc_fitness(gene,fitness); /* 適応度の計算 */
show_gene(t,gene,fitness,fp); /* 表示 */
}
/* ファイルのクローズ */
fclose(fp);
return 0;
}