# Growing Code

**コミュニティガーデンのデータで学ぶ Python の基礎**

> **概要:** コミュニティガーデンのデータ分析を通して、Python の基本的な構文と意味を学ぶ。式、変数、関数、制御フローを身につけながら、持続可能な地域の取り組みに貢献する。
>
> **バージョン:** 3.0

原文: [en.subject.pdf](en.subject.pdf)。実行例の入出力、関数名、ファイル名、指定の文字列は原文のまま記載している。解釈に迷う場合は原文を優先すること。

## 目次

- [第 I 章 まえがき](#第-i-章-まえがき)
- [第 II 章 AI に関する指示](#第-ii-章-ai-に関する指示)
- [第 III 章 はじめに](#第-iii-章-はじめに)
- [第 IV 章 全般的な指示](#第-iv-章-全般的な指示)
- [第 V 章 Exercise 0: Hello Garden](#第-v-章-exercise-0-hello-garden)
- [第 VI 章 Exercise 1: Garden Name](#第-vi-章-exercise-1-garden-name)
- [第 VII 章 Exercise 2: Garden Plot Area](#第-vii-章-exercise-2-garden-plot-area)
- [第 VIII 章 Exercise 3: Harvest Total](#第-viii-章-exercise-3-harvest-total)
- [第 IX 章 Exercise 4: Plant Age Check](#第-ix-章-exercise-4-plant-age-check)
- [第 X 章 Exercise 5: Water Reminder](#第-x-章-exercise-5-water-reminder)
- [第 XI 章 Exercise 6: Count to Harvest](#第-xi-章-exercise-6-count-to-harvest)
- [第 XII 章 Exercise 7: Seed Inventory with Type Annotations](#第-xii-章-exercise-7-seed-inventory-with-type-annotations)
- [第 XIII 章 補助リソース](#第-xiii-章-補助リソース)
- [第 XIV 章 提出と評価](#第-xiv-章-提出と評価)

---

## 第 I 章 まえがき

世界中のコミュニティガーデンで、データは成長、協力、そして影響の物語を語っている。

地域の家庭の食卓を支える収穫量の記録から、貴重な資源を守る水使用量の監視まで、あらゆる計測に意味がある。一つひとつのデータの裏には、誰かの献身がある。ボランティアが週末に費やした時間、子どもが初めて育てたトマト、何十年もの園芸の知恵を分かち合う年配のご近所さん。

Python もこうした庭のように、小さな種から力強く豊かなものへと育っていく。名前の由来は「空飛ぶモンティ・パイソン」であり、学ぶことは楽しく、誰にでも開かれ、包摂的であるべきだと思い出させてくれる。今日の Python は、科学者の気候変動の理解を助け、地域社会の資源共有の最適化を可能にし、誰もが生のデータを意味のある洞察へ変えられるようにしている。

このプロジェクトでは、実際のコミュニティガーデンのデータを分析しながら、Python の基本要素を学ぶ。プログラミングも園芸と同じく、コードと私たちが関わるコミュニティの両方の成長を育むものだと分かるだろう。

---

## 第 II 章 AI に関する指示

### 背景

学習の過程で、AI はさまざまな作業の助けになる。AI ツールの多様な能力と、それが自分の作業をどう支えられるかを時間をかけて探ること。ただし、常に慎重に扱い、結果を批判的に評価すること。コード、ドキュメント、アイデア、技術的な説明のいずれであっても、自分の質問が適切だったか、生成された内容が正確かを完全に確信することはできない。仲間は、ミスや見落としを避けるための貴重な存在である。

### 主なメッセージ

- AI を使って、繰り返しの作業や面倒な作業を減らす。
- 将来のキャリアに役立つプロンプト技術を、コーディング、非コーディングの両面で伸ばす。
- AI の仕組みを学び、よくあるリスク、偏り、倫理的な問題を予測して避けられるようにする。
- 仲間と協力しながら、技術力とパワースキルの両方を伸ばし続ける。
- **自分が完全に理解し、責任を持てる AI 生成物だけを使う。**

### 学習者のルール

- 時間をかけて AI ツールを試し、その仕組みを理解すること。そうすることで倫理的に使い、偏りを減らせる。
- プロンプトを書く前に問題について考えること。そうすることで、正確な用語を使った、より明確で詳しく適切なプロンプトを書ける。
- AI が生成したものはすべて、体系的に確認、見直し、疑問視、テストする習慣をつけること。
- 必ず仲間のレビューを受けること。自分だけの検証に頼らないこと。

### このフェーズの成果

- 汎用的なプロンプト技術と、特定分野に特化したプロンプト技術を伸ばす。
- AI ツールを効果的に使って生産性を高める。
- 計算論的思考、問題解決力、適応力、協働力を引き続き強化する。

### コメントと例

- 試験や評価など、本当の理解を示さなければならない場面に繰り返し出会う。技術力と対人スキルの両方を伸ばして備えること。
- 自分の考えを説明し、仲間と議論すると、理解の穴が見えてくることが多い。仲間との学びを優先すること。
- AI ツールはあなた固有の文脈を知らず、一般的な回答をしがちである。同じ環境にいる仲間は、より適切で正確な気づきを与えてくれる。
- AI は最もありそうな答えを生成しがちだが、仲間は別の視点や価値あるニュアンスを提供できる。品質の確認役として仲間を頼ること。

**✓ 良い例**

AI に「ソート関数はどうテストすればいい？」と聞く。いくつかのアイデアをもらい、試して、結果を仲間とレビューする。一緒にやり方を改善する。

**✗ 悪い例**

AI に関数を丸ごと書かせ、プロジェクトにコピペする。ピア評価でそれが何をしていて、なぜそうなのかを説明できない。信頼を失い、プロジェクトも落とす。

**✓ 良い例**

AI にパーサの設計を手伝ってもらう。そのロジックを仲間と一緒に順に追う。バグを2つ見つけ、一緒に書き直して、より良く、きれいで、完全に理解したものにする。

**✗ 悪い例**

プロジェクトの重要な部分を Copilot に生成させる。コンパイルは通るが、パイプの処理を説明できない。評価で根拠を示せず、プロジェクトを落とす。

---

## 第 III 章 はじめに

**Growing Code へようこそ！**

このプロジェクトでは、コミュニティガーデンの場面を通して Python の中核となる概念を学ぶ。実践的な課題に取り組みながら、プログラミングの基本概念に親しんでいく。

各課題は前の課題の上に積み上がっており、意味のある作業をしながら不可欠なプログラミングスキルを身につけられる。

> **重要:** 各課題では関数**のみ**を書くこと（メインプログラムは書かない）。各ファイルには、入出力を直接扱う、要求された関数だけを含める。`if __name__ == "__main__":` ブロックを書かないこと。ファイル内で関数を直接呼び出さないこと。関数の外にコードを書かないこと。

> **補助ツール:** 課題のテスト用に、添付ファイルとして `main.py` が提供されている。このファイルを作業ディレクトリにコピーし、`python3 main.py` を実行すると関数を簡単にテストできる。この補助ツールは関数を自動的にインポートしてテストする。

---

## 第 IV 章 全般的な指示

- 関数は **Python 3.10 以降**で書くこと。
- コードは **flake8** リンタの基準に従うこと。
- 各課題はそれぞれ独立したファイルにすること。
- 各ファイルには要求された関数のみを含めること。
- 関数名は要求された名前と完全に一致させること。
- 明記されていない限り、入力の検証やエラー処理は不要である。
- 負の数や不正な入力に対する動作は未定義である（これらのケースを処理する必要はない）。
- 型ヒントは ex0〜6 では任意だが、学習のために推奨される。**ex7 では必須**である。

> **Growing Code 固有の注意:** これは基本的な Python 構文に焦点を当てた入門プロジェクトなので、提出するのは個々の Python 関数ファイル（例: `ft_hello_garden.py`、`ft_plot_area.py` など）だけでよい。高度なプロジェクト管理ツールは後のプロジェクトで扱う。

---

## 第 V 章 Exercise 0: Hello Garden

| 項目 | 内容 |
| --- | --- |
| 関数 | `ft_hello_garden` |
| ディレクトリ | `ex0/` |
| 提出ファイル | `ft_hello_garden.py` |
| 使用可能 | `print()` |

最初の Python 関数へようこそ！ ガーデンコミュニティへの歓迎メッセージを表示するだけの関数 `ft_hello_garden` を書くこと。

```text
>>> ft_hello_garden()
Hello, Garden Community!
```

> メインプログラムではなく、関数 `ft_hello_garden()` のみを書くこと。出力は関数内で直接行うこと。

> 上の例は、Python の対話型インタプリタ内での関数の実行結果である。この例をそのまま再現しようとせず、`main.py` スクリプトを使って関数をテストすること。

---

## 第 VI 章 Exercise 1: Garden Name

| 項目 | 内容 |
| --- | --- |
| 関数 | `ft_garden_name` |
| ディレクトリ | `ex1/` |
| 提出ファイル | `ft_garden_name.py` |
| 使用可能 | `input()`, `print()` |

ガーデン名を尋ね、それを表示したあとに固定のステータスメッセージを表示する関数 `ft_garden_name` を書くこと。

```text
>>> ft_garden_name()
Enter garden name: Community Garden
Garden: Community Garden
Status: Growing well!
```

> メインプログラムではなく、関数 `ft_garden_name()` のみを書くこと。入出力は関数内で直接行うこと。

> `"Status: Growing well!"` は固定メッセージであり、常に表示のとおりに出力すること。

---

## 第 VII 章 Exercise 2: Garden Plot Area

| 項目 | 内容 |
| --- | --- |
| 関数 | `ft_plot_area` |
| ディレクトリ | `ex2/` |
| 提出ファイル | `ft_plot_area.py` |
| 使用可能 | `input()`, `int()`, `print()` |

コミュニティガーデンでは、長方形の区画の面積を知る必要がある。長さと幅を尋ね、面積を計算して表示する関数 `ft_plot_area` を書くこと。

```text
>>> ft_plot_area()
Enter length: 5
Enter width: 3
Plot area: 15
```

> メインプログラムではなく、関数 `ft_plot_area()` のみを書くこと。入出力は関数内で直接行うこと。

---

## 第 VIII 章 Exercise 3: Harvest Total

| 項目 | 内容 |
| --- | --- |
| 関数 | `ft_harvest_total` |
| ディレクトリ | `ex3/` |
| 提出ファイル | `ft_harvest_total.py` |
| 使用可能 | `input()`, `int()`, `print()` |

ある園芸家が3日間にわたって野菜を収穫した。各回の収穫量を尋ね、合計を計算する関数 `ft_harvest_total` を書くこと。

```text
>>> ft_harvest_total()
Day 1 harvest: 5
Day 2 harvest: 8
Day 3 harvest: 3
Total harvest: 16
```

> メインプログラムではなく、関数 `ft_harvest_total()` のみを書くこと。入出力は関数内で直接行うこと。

---

## 第 IX 章 Exercise 4: Plant Age Check

| 項目 | 内容 |
| --- | --- |
| 関数 | `ft_plant_age` |
| ディレクトリ | `ex4/` |
| 提出ファイル | `ft_plant_age.py` |
| 使用可能 | `input()`, `int()`, `print()` |

植物の日齢を尋ね、収穫可能（**60日より厳密に大きい**）かどうかを伝える関数 `ft_plant_age` を書くこと。

```text
>>> ft_plant_age()
Enter plant age in days: 75
Plant is ready to harvest!
>>> ft_plant_age()
Enter plant age in days: 45
Plant needs more time to grow.
```

> メインプログラムではなく、関数 `ft_plant_age()` のみを書くこと。入出力は関数内で直接行うこと。

---

## 第 X 章 Exercise 5: Water Reminder

| 項目 | 内容 |
| --- | --- |
| 関数 | `ft_water_reminder` |
| ディレクトリ | `ex5/` |
| 提出ファイル | `ft_water_reminder.py` |
| 使用可能 | `input()`, `int()`, `print()` |

最後に水やりをしてからの日数を尋ねる関数 `ft_water_reminder` を書くこと。**2日より多く**経過していれば `"Water the plants!"` を、そうでなければ `"Plants are fine"` を表示する。

```text
>>> ft_water_reminder()
Days since last watering: 4
Water the plants!
>>> ft_water_reminder()
Days since last watering: 1
Plants are fine
```

> メインプログラムではなく、関数 `ft_water_reminder()` のみを書くこと。入出力は関数内で直接行うこと。

---

## 第 XI 章 Exercise 6: Count to Harvest

| 項目 | 内容 |
| --- | --- |
| 関数 | `ft_count_harvest_iterative`, `ft_count_harvest_recursive` |
| ディレクトリ | `ex6/` |
| 提出ファイル | `ft_count_harvest_iterative.py`, `ft_count_harvest_recursive.py` |
| 使用可能 | `input()`, `int()`, `print()`, `range()`, 再帰用の補助関数の定義 |

`ft_count_harvest_iterative` と `ft_count_harvest_recursive` の2つの関数を書くこと。どちらも1から指定された数まで数え、収穫の時期まで各日を表示する。

```text
>>> ft_count_harvest_iterative()
Days until harvest: 5
Day 1
Day 2
Day 3
Day 4
Day 5
Harvest time!
>>> ft_count_harvest_recursive()
Days until harvest: 5
Day 1
Day 2
Day 3
Day 4
Day 5
Harvest time!
```

> メインプログラムではなく、関数 `ft_count_harvest_iterative()` と `ft_count_harvest_recursive()` のみを書くこと。入出力は関数内で直接行うこと。

再帰版では、次のようなさまざまな方法が認められる。

- メイン関数の内側に入れ子の補助関数を使う
- デフォルト引数を使う
- メイン関数から呼び出す別の補助関数を使う

> 自分に最も納得のいく方法を選ぶこと。再帰版と反復版の出力は同一でなければならない。

---

## 第 XII 章 Exercise 7: Seed Inventory with Type Annotations

| 項目 | 内容 |
| --- | --- |
| 関数 | `ft_seed_inventory` |
| ディレクトリ | `ex7/` |
| 提出ファイル | `ft_seed_inventory.py` |
| 使用可能 | `print()`, 文字列メソッド |

ガーデンのコーディネーターは、正確なデータ型で種の在庫を管理する必要がある。種のパケットを管理し、さまざまな種類と数量の情報を表示する関数 `ft_seed_inventory` を書くこと。

```text
>>> ft_seed_inventory("tomato", 15, "packets")
Tomato seeds: 15 packets available
>>> ft_seed_inventory("carrot", 8, "grams")
Carrot seeds: 8 grams total
>>> ft_seed_inventory("lettuce", 12, "area")
Lettuce seeds: covers 12 square meters
```

関数のシグネチャは次のとおりにすること。

```python
def ft_seed_inventory(seed_type: str, quantity: int, unit: str) -> None:
```

> メインプログラムではなく、関数のみを書くこと。出力は関数内で直接行うこと。

> 種の名前の先頭は大文字になっている点に注意すること。文字列オブジェクトのメソッドを使える。

> 対応する単位は `"packets"`（packets available）、`"grams"`（grams total）、`"area"`（covers X square meters）である。それ以外の単位では、`"Unknown unit type"` だけを表示し、同じ行に他の情報を含めないこと。

> 冒頭で述べたとおり、ここでは Python の型ヒント（typing）を必ず使うこと。型は **mypy** で確認すること。

---

## 第 XIII 章 補助リソース

学習を支援するため、課題を簡単にテストできる `main.py` ファイルが提供されている。

Python を始めたばかりで、まだ main 関数の書き方を知らない段階なので、この補助ツールは次のことを行う。

- 課題の関数を自動的にインポートして実行する
- 問題が起きたときに分かりやすいエラーメッセージを表示する
- 個別の課題、または全課題をまとめてテストできる
- Python のインポートの仕組みを理解する助けになる

使うには、ターミナルで `python3 main.py` を実行し、テストする課題を選ぶ。課題ファイル（`ft_plot_area.py` など）が `main.py` と同じフォルダにあることを確認すること。

> この補助ファイルは読みやすく学習に役立つように作られている。コードを見て仕組みを理解してもよいが、まずは自分の解答を書くことに集中すること。

> この補助ファイルは学習支援専用である。提出する解答は自分自身の成果物であり、概念の理解を示すものでなければならない。

---

## 第 XIV 章 提出と評価

通常どおり、課題を自分の Git リポジトリに提出すること。ディフェンス（評価）では、リポジトリ内の成果物のみが評価される。ファイル名が正しいか、ためらわず再確認すること。

> 評価では、コードの説明、実行の追跡、解答の修正を求められることがある。自分が書いたすべての行を理解しておくこと。

このプロジェクトでは、各課題で要求されたファイルのみを提出すればよい。Python の基礎への理解が伝わる、きれいで読みやすいコードを書くことに集中すること。
