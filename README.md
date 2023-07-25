# Tetris2D *v0.0*
2D 테트리스 게임 구현 프로젝트의 *v0.0*입니다.
<br><br>


## Platform

`Tetris2D` *v0.0*은 `Windows Platform`만 지원합니다.  
<br><br>


## Requirements

`Tetris2D` *v0.0*를 유지 보수를 수행하기 위한 요구 사항은 다음과 같습니다.
- [git](https://git-scm.com/)
- [Visual Studio 2019 이상](https://visualstudio.microsoft.com/)
<br><br>


## Language

`Tetris2D` *v0.0*은 `C++17` 으로 구현되었습니다.  
> `Windows`에 특화된 코드도 존재하므로, `Linux`나 `MacOSX`에서는 빌드되지 않습니다.

<br><br>


## Clone

`CMD` 에서 다음과 같이 수행하시면 *v0.0*의 저장소 복제본을 얻을 수 있습니다.

```
git clone https://github.com/ChoiJiOne/Tetris2D --single-branch -b v0.0
```
<br><br>


## Structure

`Tetris2D` *v0.0*의 프로젝트 구조는 다음과 같습니다.
```
├─Engine
│  ├─Bin
│  ├─Script
│  ├─Shader
│  ├─Source
│  │  ├─Private
│  │  └─Public
│  └─ThirdParty
│      ├─miniaudio
│      └─stb
└─Game
    ├─Content
    │  ├─Audio
    │  ├─Config
    │  ├─Font
    │  └─Texture
    └─Source
        ├─Private
        └─Public
```
<br><br>


## Generate Visual Studio Solution

`Tetris2D` *v0.0*은 `Visual Studio Solution` 생성 자동화를 지원합니다.  
`GenerateProjectFiles.bat`를 실행하면 `Visual Studio Solution`을 얻을 수 있습니다.  
만약, `Visual Studio 2022`로 진행하고 싶다면 다음과 같이 배치 스크립트를 수정합니다.  
```
@echo off
Engine\\Script\\GenerateProjectFiles.bat Tetris2D vs2022 CrashDump
```

<br><br>


## Build Without Visual Studio Solution

`Tetris2D` *v0.0*은 `Visual Studio Solution` 없이 빌드를 수행하는 기능을 지원합니다.

> `msbuild.exe` 경로를 반드시 환경 변수에 등록해야 합니다.

솔루션을 빌드하는 스크립트는 `Debug`, `Release`, `Shipping` 세 가지 파라미터를 받습니다.
파라미터를 전달하지 않으면, 스크립트는 실행되지 않습니다.

| 종류 | 설명 |
|:---:|:---|
| `Debug`    | 최적화를 수행하지 않고, 디버그 심볼(.pdb)을 생성합니다. |
| `Release`  | 최적화를 하지만 `Shipping`만큼은 하지 않고, 디버그 심볼(.pdb)을 생성하지 않습니다. |
| `Shipping` | 컴파일러가 수행할 수 있는 모든 최적화를 수행하고, 디버그 심볼(.pdb)을 생성하지 않습니다. |

빌드 스크립트를 실행하기 위해서는 `CMD`에서 다음과 같이 수행합니다.
```
> Build.bat <option>
```

예를 들어, `Debug` 모드로 빌드를 수행하고 싶다면 다음과 같이 수행합니다.
```
> Build.bat Debug
```

만약, `Visual Studio 2022`로 진행하고 싶다면 다음과 같이 배치 스크립트를 수정합니다.

```
@echo off

SET option=%1
Engine\\Script\\Build.bat Tetris2D vs2022 %option%
```
<br><br>


## How to play

`RunGame.bat`를 클릭해서 실행하면 시작화면에서 시작화면에서 `START`와 `QUIT` 버튼을 클릭할 수 있습니다. `START`를 클릭하면 게임을 시작하고 `QUIT` 버튼을 클릭하면 게임을 종료하게 되는데, 테트로미노 조작은 `LEFT`는 왼쪽, `RIGHT`는 오른쪽, `DOWN`은 아래쪽, `UP`은 회전, `SPACE`는 가장 아래로 이동할 수 있습니다. 게임 플레이 화면 왼쪽에서 사운드 관련 버튼을 클릭하면 제어할 수 있고, `ESC`키를 누르면 게임을 일시 중지시킬 수 있습니다.
