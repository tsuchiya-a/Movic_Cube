Movic_Cube
==========
メディアアート制作事例として動作するサイコロ「Movic Cube」を制作しました。  
この制作を通して開発したコンポーネントを公開しています。  
現在公開しているMovic Cubeのバージョンは以下のとおりです。  
* 光るサイコロ：Movic Cube(ver.Luminous)  
 - 加速度センサとフルカラーLEDを持つサイコロ

動作環境
--------
Windows7 32bit,64bit  
OpenRTM-aist-1.1.0-RELEASE（C++版)  
Eclipse 3.8.1 + OpenRTM Eclipse tools 1.1.0-RC4  

コンポーネント群
----------------
本リポジトリで公開しているコンポーネントは以下の通りです。

* Calibration_forAcceleration3D  
加速度センサのキャリブレーションを行うコンポーネント。型変換に用いることができる。
* DiceCalculation  
サイコロの出目を計算するコンポーネント。
* DiceColorPattern  
サイコロの出目によって色を変えるコンポーネント。
* DiceMemory  
サイコロの出目を記憶するコンポーネント。
* DiceSort  
複数のサイコロをソートするコンポーネント。
* RGBTester  
RGBの色を表示するコンポーネント。
* autoGradation  
グラデーションになるようにRGBを出力するコンポーネント。パラメータでグラデーションを調整することができる。
* convRGBColor  
入力された値をRGB（0~255の値）に変換して出力するコンポーネント。型変換に用いることができる。
