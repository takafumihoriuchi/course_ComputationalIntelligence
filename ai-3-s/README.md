# Introduction to Games and Game Theory  

### Contents  
- ゲームの研究の背景
- ゲーム木の探索（minmax法、alpha-beta法、and-or木）
- ゲーム理論（囚人のジレンマ、ほか）
- 心得
- 参考資料  


## ゲームの研究の背景  

研究分野として「ゲーム理論」と言った時の「ゲーム」は、もちろん、チェスやバックギャモンなどのゲームを意味する。
人工知能研究（＊）では、環境が簡単に表現できるというゲームの好都合な性質上、これを研究対象として現実世界の問題の解決に応用しようとしている。また、ゲームには「相手が何をするかわからない」という性質があり、これも現実世界を簡略化しているという点で都合が良い。

ルールがあらかじめ定まっているゲームであっても、全数探索をしていては現実的な時間で答えを導くことはできない。（いわゆる「おねいさんの問題」になってしまう。）
そこで、有効な戦略を考える必要がある。  
＝＞　探索木を制限する（枝刈り）  
＝＞　相手の手を推測する

**ゲームは探索問題**  
オセロやチェスなどのゲームを、次のように考える：
- 初期状態	（駒の最初の位置など）
- オペレータ	（指し手）
- 終端テスト	（ゲームが決着したかの判定）
- 効用関数	（utility function、結果を数値として戦略に利用）
- 利得関数	（payoff function、結果を数値として戦略に利用）  

このようにして構成される木構造を「ゲーム木」と呼ぶ。
このように考えると、ゲームを遊ぶことは、詰まる所は「探索木を解く」ことに他ならない。  


（＊「人工知能」という言葉には明確な定義はないが、研究分野としての人工知能は、人間のような賢さを機械で実現する試みのこと。（私見：人工知能と言った時には人間のレベルの知能を実現することを指すが、マウス程度、もしくはバグ程度の人工的な知能も未だ実現されていないと理解している。生物研究などでマウスに協力してもらっているように、人工知能分野でもそれらの脳をリバースエンジニアリングする試みが行われているのかどうかが少し気になる。））


## ゲーム木探索  

　ここから題材として扱うゲームは、チェスや将棋のように、自分と相手が交互に手を指して対戦するものとする。したがって、探索木は、自分と相手の指す手で枝分かれしていく。  
また、結果（ゴール状態）は、「勝ち」、「負け」、「引き分け」の３種類があり、エージェントは「勝ち」を目指して探索を進めることになる。


### ミニマックス法  

　まず、ミニマックス法（＊）について説明する。ミニマックス法とは、「相手にとって最良の手は、自分にとっては最悪の手」という一対一の対戦における事実を前提に成り立っている。つまり、自分の番での枝分かれでは最良の手を選択し、相手の番の枝分かれでは最悪の手を選択することで、勝利を探索する。これが「ミニmin・マックスmax法」の名称の由来である。これは、一対一の対戦に限られ、３プレイヤー対戦などでは「敵の敵は味方」的な考え方が出現してくるため、ミニマックス法は単純には成り立たなくなる。  
　探索木の生成方法としては、まず、すべての選択を含んだ木を構成する。そして、葉を評価する。tick-tack-toeのような単なる勝敗を決定すれば十分なゲームでは、勝利の葉を「＋∞」、敗北の葉を「ー∞」とすれば良い。チェスや将棋のように勝ちにも「圧勝」、「なんとか勝利」のように様々な盤面を考えるべきゲームでは、勝ちの度合いを数値化しても良い。葉の評価ちが決定されれば、次は高さ１のノード、つまり葉の一つ上のノードを評価する。ここでは、自分の番か相手の番かによって、子ノードのうち、最良または最悪の評価をそのまま持ってくる。これを根（初期状態）に至るまで木の上の方向に繰り返し、各ノードの効用を決定する。  
探索木が完成すれば、あとは木の根から自分の番であるか相手の番であるかによって、最良の手、最悪の手を選択していき、自分が勝てる、もしくは負けない経路を探索する。以上がミニマックス法の仕組みである。  
　ミニマックス法の特徴の良い点は、最悪の結果を回避することができることが挙げられる。逆に悪い点としては、ゲームのすべての局面を探索するため、計算量（時間・空間ともに）が膨大になってしまい、tick-tack-toeのような単純な（状態数の少ない）ゲームであれば対応できるものの、囲碁のように星の数よりも状態数が多いゲームに関しては、ミニマックス法により現実的な資源で資源で解を導く事は不可能な場合もある。このような事態を免れるための工夫として、「深さNで探索を打ち切る」という策が考えられる。つまり終端状態以前に探索を打ち切るということ。この場合、「勝ち・負け」を評価するのではなく、盤面を勝率の数値に置き換える評価関数が必要となる。チェスの場合は、かなりの精度を叩き出すこのような評価関数が開発されたらしい。  

（＊決して*ベイマックス法*ではないことに注意）


#### アルファベータ枝刈り  

　ミニマックス法の説明で、探索木を構成する際に全数探索となってしまうと現実的な資源で解くことができなくなってしまうと述べたが、これを解消する方法の一つに「アルファベータ法」がある。つまり、アルファベータ法とは、ミニマックス法を、不要な探索を省略することで簡略化したものである。
アルファベータ**枝刈り**とは、探索木の枝をアルファベータ法で省略していくことを意味する。  
アルファベータ法の概要について良い説明があったので引用[1]する。
>Alpha-Beta pruning is not actually a new algorithm, rather an optimization technique for minimax algorithm. It reduces the computation time by a huge factor. This allows us to search much faster and even go into deeper levels in the game tree. It cuts off branches in the game tree which need not be searched because there already exists a better move available. It is called Alpha-Beta pruning because it passes 2 extra parameters in the minimax function, namely alpha and beta.
アルファベータ法の注意点として、葉は終了した時の評価値を保持しているが、それが最大のものが戦略的に最も良いとは限らないとうことである。これは、ゲームでは、相手にとって悪い手を選択することを考慮に入れつつ、自分にとって良い手を選択する必要があるためである。アルファベータ法をC言語で記述したものが**minmax.c**である。  

　以上がミニマックス法およびそれを効率化したアルファベータ法の説明であった。次に、別のタイプの探索木である「AND/OR木」を取り上げる。

### AND/OR木  

まず**分割問題**について説明する。分割問題とは、ある問題をいくつかの小問題に分けて問題解決する手法である。ここでは、元の問題を**親問題**、分割した問題を**子問題**という。また、問題間の関係について、次の二つの結合を定義する。  
**AND結合**: 子問題をすべて解決する必要がある場合（例：大学に行く＝＞家を出る、駅に向かう、電車に乗る、など）  
**OR結合** : 子問題を一つ解決すれば良い場合（例：昼を食べる＝＞ハヤシライス屋に行く、唐揚げ屋に行く、など）  
これら二つの結合を用いて分割問題を階層的に表現したものが**AND/OR木**である。下の画像に病気の診断に関するAND/OR木の例を示す。  
ミニマックス法における探索木はゴールつまり適切な葉を探すことを目的としていた（経路も大切なのではないか？）が、AND/OR木では、**解グラフ**を探すことを目的とする（構文のようなものを結果として得られる）。解グラフとは、次のような部分木Gのことをいう。  
  
**解グラフの条件**：  
- Gは初期ノード（根）を含む
- Gに含まれるANDノードのすべての子ノードも、Gに含まれる
- Gに含まれるORノードの子ノードは、一つだけGに含まれる
- Gの末端ノード（葉）は、元々のAND/OR木の末端ノードであり、解の一部となりうるもの  

解グラフを求めるための、AND/OR木のアルゴリズムを次に記す。  

**アルゴリズム**:    
**Step-1**  
頂点だけのグラフを作り、このグラフをOPENリストに加える。  
**Step-2**  
OPENリストが空なら失敗として終了。OPENリストからグラフを一つ選択し、これをgとする。gが解グラフの条件を満たして入れば、これを出力して終了。  
**Step-3**  
gを**展開**し、グラフを生成する。生成されたグラフを**評価**して、残ったグラフをOPENリストに加える。Step-2を実行する。  
  
**展開法**:  
gの各リーフについて、  
ANDノードであれば、その子ノードをすべて加える。  
ORノードであれば、その子ノードをひとつずつ加えたグラフを子ノードの数だけ作る。  
  
**評価法**:  
- gの各リーフを調べ、  
当初のAND/OR木の目標ノードであれば"S"のラベル、  
それ以上展開できないノードであれば"N"のラベルをつける。
- gのリーフ以外のノードに関して、  
それがANDノードであるときは、  
そのすべての子ノードに"Sのラベルがあれば、"S"のラベルをつけ、  
ひとつでも"N"があれば、"N"のラベルをつける。  
それがORノードであるときは、  
その子ノードと同じラベルをつける。
- 頂点が"S"なら解グラフとみなし、"N"なら評価の結果としてこのグラフは排除される（？）。  
なお、"N"は、受け入れられないノードや、探索の限界で途中で切られたものを意味する。  

まとめると、AND/OR木は、生成規則（ルール）によって生成され得る単一の結果について、それらすべての木構造を表す方法であると言える。以上が、AND/OR木についての説明であった。
  
![an example of an AND/OR tree](http://ix9.jp/softcomputing/img/ai/fig42.png)  


## ゲーム理論  

ゲーム理論とは何か。それは、二組以上のプレイヤーの合理的かつ戦略的な意思決定を記述する数学的な枠組みである。ゲーム理論が初めて提唱されたのは、1994年に発表されたジョン・フォン・ノイマンとモルゲンシュタインの「ゲームの理論と経済活動」。それ以降、計算機科学を中心とし、経済学、社会学、生物学、防衛学など、様々な分野における論理的枠組みとして利用されている。  

計算機科学におけるゲーム理論とは、二つのエージェント間のインタラクション構造（関係）を表現し、最適な**戦略**を決定するための方法のことである。ここでの戦略とは、目指すゴール状態や対応の基本方針を決定することを意味する。これは、相手との関係（協調、調整、敵対）により、目指すべき目的が変化するため、必要な情報となる。  

**ポイント**
- 各エージェントは常に合理的な選択をする。
- **支配戦略**とは、相手がいかなる戦略を取っても、他よりは利得が高くなる戦略。支配戦略が存在するときは、エージェントは必ずこの支配戦略を採用する。
- **支配戦略均衡**とは、**対象ゲーム**で全エージェントに支配戦略が存在するとき、彼ら全てがこの支配戦略を選択するような状態。対象ゲームとは、各エージェントの行動選択肢を行列として表現したときに、エージェント間でそれが対称行列となっているようなゲームのことをいう。
- **反復支配戦略**とは、一方に支配戦略があることにより、元々は支配戦略はなかった他方のエージェントの戦略も一パターンに限定されるような状態のことをいう。
- **ゼロサムゲーム**とは、各要素がa(i,j)とb(i,j)で表される利得行列において、a(i,j) = -b(i,j)となるようなゲームのことをいう。アマゾンが「市場はゼロサムゲームではない」と主張して脅威とみなされることを緩和するためにも用いた表現。自社が成功した場合、他者は失敗するとは限らないのが、ゼロサムゲームで*ない*場合。  

**囚人のジレンマ**（すごく嫌なジレンマ）  

>共同で犯罪を行ったと思われる囚人A、Bを自白させるため、検事は2人に次のような司法取引をもちかけた。
>本来ならお前たちは懲役5年なんだが、もし2人とも黙秘したら、証拠不十分として減刑し、2人とも懲役2年だ。
>もし片方だけが自白したら、そいつはその場で釈放してやろう（つまり懲役0年）。この場合自白しなかった方は懲役10年だ。
>ただし、2人とも自白したら、判決通り2人とも懲役5年だ。
>この時、2人の囚人は共犯者と協調して黙秘すべきか、それとも共犯者を裏切って自白すべきか、というのが問題である。なお彼ら2人は別室に隔離されており、相談することはできない状況に置かれているとする。

| | 囚人B強調 | 囚人B裏切り |
| ------------ | ------------- | ------------- |
| 囚人A強調 | (2年, 2年) | (10年, 0年) |
| 囚人A裏切り | (0年, 10年) | (5年, 5年) |

施行が一回だけであるなら、裏切りが最適戦略となるが、詳しい研究により、同じ相手と複数回繰り返しプレイすることがわかっていれば、協調が生まれる可能性があることが明らかになっている（らしい）（朗報）。
「囚人のジレンマ」のコンセプトは、自動運転の交通状況などのAI研究のほか、人間社会や生物間での研究にも用いられることが多い。  
  
以上  
  
### 心得
>本当に理解するためには、実装を自分で再現することが大切。

### references
[1] https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-4-alpha-beta-pruning/  
[2] http://ix9.jp/softcomputing/ai-4.shtml  
[3] https://ja.wikipedia.org/wiki/%E5%9B%9A%E4%BA%BA%E3%81%AE%E3%82%B8%E3%83%AC%E3%83%B3%E3%83%9E  