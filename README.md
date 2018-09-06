# kalmanfilter

卡爾曼濾波器測試專案

## kalmanfilter_1d

> 單軸加速儀卡爾曼濾波器驗證測試

* `kmath.c` `kmath.h` 卡爾曼濾波器所需的數學函式
* `kalmanfilter.c` `kalmanfilter.h` 卡爾曼濾波函式
* `main.c` 卡爾曼濾波器模擬資料

### build

clone this project

```
git clone https://github.com/yuhao-kuo/kalmanfilter.git kalmanfilter
```

change to project directory

```
cd kalmanfiler
```

build project

```
make kalman1d
```

run kalman test

```
./kalman1d.o -o kalman.log
```
    
### 執行參數

| 參數 | 意義 | 附帶資料 |
|---|---|---|
| h | help | - |
| o | 指定計算結果儲存位置 | path and name |

---

## kalmanfilter_2d

> 雙感測器卡爾曼濾波器

* `kalmanfilter.c` `kalmanfilter.h` 卡爾曼濾波函式
* `main.c` 卡爾曼濾波器模擬

### build

clone this project

```
git clone https://github.com/yuhao-kuo/kalmanfilter.git kalmanfilter
```

change to project directory

```
cd kalmanfiler
```

build project

```
make kalman2d
```

run kalman test

```
./kalman1d.o -i sensors.txt -o kalman.log -s
```

### 執行參數

kalman2d支援長參數功能, 參數內容請參見下表

| 參數 | 意義 | 附帶資料 |
|---|---|---|
| -h --help | help | - |
| -o --output | 指定計算結果儲存位置 | path and name |
| -i --input | 數值資料位置 | path and name |
| -s --show | 顯示測試數值 | - |
