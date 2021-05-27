# FreeRTOS_for_PSoC5LP

PSoC5LP CY8CKIT-059 で FreeRTOS を使ってマルチタスク処理を実行する方法まとめ

## 1. 実行に必要なもの

- PSoC5LP CY8CKIT-059 (PSoC 本体)
- PSoC Creator (PSoC プログラム開発環境) : https://japan.cypress.com/products/psoc-creator-integrated-design-environment-ide よりダウンロード．Cypress への登録必要．本プログラムの開発は PSoC Creator 4.4 で行った.
- FreeRTOS (FreeRTOS のライブラリ群) : https://freertos.org/index.html の「Download FreeRTOS」からダウンロード．FreeRTOS 202104.00 ('21/5/27 現在．FreeRTOS Kernel や example projects が含まれている方．) をダウンロード


## 2. プロジェクト作成準備

