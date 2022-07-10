
# モジュール

## モジュールはルートヘッダを持つ

### モジュールが公開するインターフェイスをすべて定義

## モジュールが別モジュールへ依存する場合

### 自身のルートヘッダ内で依存するモジュールのルートヘッダをインクルード

ルートヘッダ以外の外部ヘッダのインクルードを禁止

## 依存関係は3種類

### Require
エフェクトモジュールはレンダリングモジュールが必須
```cpp
// Modules/Effect/Effect.h

#include "Modules/Render/Render.h"
```

### Either
ムービーモジュールは音が鳴らせれば良いので、どちらかのモジュールがあれば良い
```cpp
// Modules/movie/movie.h

#if VIA_MODULE_WWISE
#include "Modules/Wwise/Wwise.h"
#else
#include "Modules/Sound/Sound.h"
#endif
```

### Optional
物理シミュレーションモジュールはレンダリングモジュールがなくても動作するが、あればGPUを利用したクロスシミュレーションなどを利用できる
```cpp
// Modules/Physics/Physics.h

#if VIA_MODULE_RENDER
#include "Modules/Render/Render.h"
#endif
```


