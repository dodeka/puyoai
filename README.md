puyoai
======


[![Build Status](https://travis-ci.org/puyoai/puyoai.svg?branch=master)](http://travis-ci.org/puyoai/puyoai)

ぷよぷよ通のAIを書くためのフレームワークです。

実際に動いているAIの例: http://www.nicovideo.jp/watch/sm26167419

## 前提環境

### OS

現状、Mac OS X(10.10 Yosemite) と Ubuntu Linux 14.04 でビルドできることを確認しています。

古めの Linux (Ubuntu 12.04 など)では、gcc や clang が古いので、もしかしたらコンパイルが通らないかもしれません。

また、32bit環境では全くテストしていません。

### コンパイラ

clang-3.4 以降、と gcc-4.7 以降でのみテストしています。

基本的に C++11 で書かれているため、C++11 の対応が悪いコンパイラではコンパイルできないかもしれません。

### ハードウェア (CPU)

高速化のため、CPU に AVX 命令が載っていることを前提にしている箇所があります。
すなわち、2011 年〜 2012 年以降の CPU のみを対象にしています。
現状は AVX2 は前提にしていません。

## ビルド方法

### 必要なライブラリ

次のライブラリが必要ですので、インストールしてください。(Linux と mac でのインストール方法は後述。)

* google-gflags
* google-glog

GUI を付与したい場合、さらに次のライブラリが必要です。

* SDL 2.0
* SDL_ttf (2.0)
* SDL_image (2.0)

似非 GUI として http サーバとして動かす場合は次のライブラリが必要です。
* microhttpd

ビデオキャプチャーをしたい場合、さらに次のライブラリが必要です。

* gcrypt
* lib-usb1.0

その他、ライブラリではないですがビルドツールとして `cmake` `make` が必要です。
また `ninja` を使えるとより利便性が上がるかもしれません。

#### Mac OSX の場合

Mac の場合、homebrew を使うと楽です。
Xcode、コマンドラインツール、homebrew をインストールしてください。
デフォルトで `/usr/local/include` などを見ないようになっている可能性がありますが、`xcode-select --install` を叩いておくと解決します。

次のコマンドで必要なものが入るとおもいます。

    $ brew install pkg-config
    $ brew install cmake gflags glog sdl2 SDL2_ttf SDL2_image ffmpeg libusb libgcrypt

#### Linux (Ubuntu) の場合

Debian 系 Linux の場合、apt を使うと楽です。
次のコマンドで必要なものが入るとおもいます。

    $ sudo apt-get install git clang cmake
    $ sudo apt-get install libgoogle-glog-dev libgflags-dev
    $ sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
    $ sudo apt-get install libmicrohttpd-dev
    $ sudo apt-get install libffms2-dev libusb-dev libcrypto++-dev
    $ sudo apt-get install ninja-build

### make のしかた

cmake を用いて Makefile を生成し、make することを前提にしています。

out ディレクトリを掘って、そこでビルドするようにしてください。ビルドの種類によって、ディレクトリを分けると楽かもしれません。

デフォルトビルド (-O2, -g)

    $ mkdir -p out/Default; cd out/Default
    $ cmake ../../src
    $ make -j8
    $ make test

デフォルトビルドは、実行が高速であり、クラッシュ時にシンボルが取れるので、AIの開発中にオススメです。

デバッグビルド (-g)

    $ mkdir -p out/Debug; cd out/Debug
    $ cmake -DCMAKE_BUILD_TYPE=Debug ../../src
    $ make -j8
    $ make test

デバッグビルドでは、DCHECK が有効になり、より多くのチェックが実行時に行なわれます。
なにか新しい機能を作ってテストしている最中などはデバッグビルドが最もオススメです。

リリースビルド (-O3)

    $ mkdir -p out/Release; cd out/Release
    $ cmake -DCMAKE_BUILD_TYPE=Release ../../src
    $ make -j8
    $ make test

最終的に実行したい場合は、リリースビルドでビルドしたものを使うと良いでしょう。最も高速です。

* `gflags` と `glog` が `cmake` に発見されなかった場合、`cmake` が成功しません。
* SDL と SDL_ttf がない場合、`cmake` は成功しますが、GUIがつきません。
* キャプチャ関連については、[capture/README.md](https://github.com/puyoai/puyoai/tree/master/src/capture) を参照してください。

[build/](https://github.com/puyoai/puyoai/tree/master/build) 以下にいくつかビルド用のスクリプトが置かれていますが、`ninja` でビルドすることを前提にしています。

## 実行

    $ cd out/Release
    $ ./duel/duel ./cpu/sample/sample ./cpu/sample_rensa/sample_rensa

`duel` は対戦サーバで、筐体のような役割を果たします。1 つ目の引数 `sample` は 1P 側を担当する AI、2 つ目の引数 `sample_rensa` は 2P 側を担当する AI です。
`duel` にオプションを渡すことで対戦速度を上げたり、ぷよの色を指定できたり、といろんな機能を引き出すことができます。ドキュメント化されていないものもありますが、

    $ ./duel/duel --help

とすると実装されている機能と必要なオプションが全部出てくるのでとりあえずはそちらを参照してください。

## ディレクトリの説明

* src/ 主なプログラムのソース。
* build/ ビルド関連のスクリプトなど。意味のわかる方のみ使ってください。
* arduino/ Wii 実機やアーケード基板と接続する際に使う、arduino関連のソース。
* data/    フォントとか画像とか。
* testdata/ キャプチャー用のテストデータ。
* tools/ いろいろなツール類。なぜ src/ 以下じゃないのか？
* deprecated/ 過去のソース。必要な物をサルベージしたら消される運命にあります。参照用。
