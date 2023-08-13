# philosophers

42 (https://42.fr/en/) の課題として、「食事する哲学者の問題」 (https://en.wikipedia.org/wiki/Dining_philosophers_problem) を題材にした並列処理プログラムを実装しました。

デッドロックを回避するために、奇数番目の哲学者は左手のフォークを最初に手に取り、偶数番目の哲学者は右手のフォークを最初に手に取る方法を採用しました。

本実装は、42におけるC言語の規約に基づいて実装しています。規約ルールを以下にまとめます。
- 42のC言語のコード規約に従うこと
  - ファイル1つにつき関数5つまで
  - 関数の中は25行まで
  - for文禁止、など
- 未定義動作、クラッシュ、メモリリーク禁止

```sh
$ cd philo

# run test
$ make test
```
