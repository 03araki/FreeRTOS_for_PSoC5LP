# FreeRTOS_for_PSoC5LP

PSoC5LP CY8CKIT-059 で FreeRTOS を使ってマルチタスク処理を実行する方法まとめ

- FreeRTOS_for_PSoC5LP.cywrk : FreeRTOS を用いたサンプルプログラムのプロジェクトファイル
- FreeRTOS_for_PSoC5LP.cydsn/ : サンプルプログラムの本体 (FreeRTOS の必要ファイル含む)

サンプルプログラム : マルチタスク処理で２つの LED の点滅と UART の送信・受信処理を行うプログラム


## 実行に必要なもの

- PSoC5LP CY8CKIT-059 (PSoC 本体)
- PSoC Creator (PSoC プログラム開発環境) : https://japan.cypress.com/products/psoc-creator-integrated-design-environment-ide よりダウンロード．Cypress への登録必要．本プログラムの開発は PSoC Creator 4.4 で行った.
- FreeRTOS (FreeRTOS のライブラリ群) : https://freertos.org/index.html の「Download FreeRTOS」からダウンロード．FreeRTOS 202104.00 ('21/5/27 現在．FreeRTOS Kernel や example projects が含まれている方．) をダウンロード


## プロジェクト作成準備

１．FreeRTOS を使ったプロジェクトを作成するために必要なファイルをまとめるための空のフォルダ (ここでは FreeRTOS とする) を準備．


２．ダウンロードしたファイル (FreeRTOSv202104.00.zip) を展開し，その中から以下のファイルを１．で作成したフォルダにコピー．(サブフォルダは作らずに，以下のファイルをすべて１．のフォルダにコピーする)
- FreeRTOS/Source/croutine.c
- FreeRTOS/Source/list.c
- FreeRTOS/Source/queue.c
- FreeRTOS/Source/tasks.c
- FreeRTOS/Source/timers.c
- FreeRTOS/Source/include/croutine.h
- FreeRTOS/Source/include/deprecated_definitions.h
- FreeRTOS/Source/include/FreeRTOS.h
- FreeRTOS/Source/include/list.h
- FreeRTOS/Source/include/mpu_wrappers.h
- FreeRTOS/Source/include/portable.h
- FreeRTOS/Source/include/projdefs.h
- FreeRTOS/Source/include/queue.h
- FreeRTOS/Source/include/semphr.h
- FreeRTOS/Source/include/stack_macros.h
- FreeRTOS/Source/include/StackMacros.h
- FreeRTOS/Source/include/task.h
- FreeRTOS/Source/include/timers.h
- FreeRTOS/Source/portable/MemMang/heap_2.c
- FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
- FreeRTOS/Source/portable/GCC/ARM_CM3/portmacro.h
- FreeRTOS/Demo/CORTEX_CY8C5588_PSoC_Creator_GCC/FreeRTOS_Demo.cydsn/FreeRTOSConfig.h

３．コピーしたファイルのうち，FreeRTOSConfig.h の 41 行目
```
#include <device.h>
```
を
```
#include <project.h>
```
に変更．


## FreeRTOS を使ったプロジェクトの作成

１．PSoC Creator で CY8C5888LTI-LP097 用の空プロジェクトを作成

２．作成されたフォルダ内 (main.c がある場所) に前章で準備した FreeRTOS のファイルをフォルダごとコピー

３．「Workspace Explorer」の Project (上から2番目?) で右クリックし，[Add] - [New Folder] で新しいフォルダを作成し，「FreeRTOS」という名前にしておく

４．作成した「FreeRTOS」フォルダを選択して右クリックし，[Add] - [Existing Item...] を選択して，２．でコピーしたフォルダ内のファイルをすべて選択して追加

５．メニューバーの [Project] - [Build Settings...] を選択し，表示されたダイアログの [ARM GCC ...] - [Compiler] - [General] 内の「Additional Include Directories」に「.\FreeRTOS」を追加して OK ボタンを押す．(２．でコピーした FreeRTOS フォルダをInclude Directory に含める)

FreeRTOS の使い方はサンプルコードや FreeRTOS のサイト (https://freertos.org/index.html) を参照すること．


## 参考

- https://qiita.com/Tanba28/items/373f6ab8ef21a4cd964b
- http://idken.net/posts/2017-09-23-freertos_status/
- https://iotexpert.com/freertos-psoc-examples/
