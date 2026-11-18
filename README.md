# Paikorea firmware (QMK + Vial)

[Paikorea](https://github.com/Ksty7879/Paikorea) 스플릿 키보드용 QMK 펌웨어입니다. [vial-qmk](https://github.com/vial-kb/vial-qmk) 기반이라 [Vial](https://get.vial.today/)에서 키맵을 실시간으로 바꿀 수 있습니다.

- MCU: RP2040-Zero ×2 (한쪽에 하나씩)
- 키: 한쪽 19키, 총 38키 (Kailh PG1316S)
- 스플릿 통신: TRRS 1선 반이중 시리얼 (GP11)
- 트랙패드: Azoteq TPS43 (IQS572), 양쪽에 하나씩, I2C0 (GP8 SDA / GP9 SCL)

## 펌웨어 받기

`main`에 푸시할 때마다 GitHub Actions가 펌웨어를 빌드합니다. **Actions → 최근 실행 → Artifacts → `paikorea-firmware`** 에서 받으세요. `v1.0` 같은 태그를 푸시하면 Releases에도 올라갑니다.

| 파일 | 용도 |
| --- | --- |
| `paikorea_vial_left.uf2` | 왼쪽(뒷면 조립) 보드 — Vial 지원 |
| `paikorea_vial_right.uf2` | 오른쪽(앞면 조립) 보드 — Vial 지원 |
| `paikorea_default_*.uf2` | Vial 없는 일반 QMK (테스트용) |

## 플래싱

1. RP2040-Zero의 **BOOT** 버튼을 누른 채 USB를 꽂거나, 이미 QMK가 들어가 있으면 **RESET을 빠르게 두 번** 누릅니다.
2. `RPI-RP2` 드라이브가 뜨면 해당 쪽 `.uf2`를 끌어다 놓습니다.
3. 반대쪽도 같은 방법으로 합니다. **왼쪽엔 left, 오른쪽엔 right** 파일을 넣어야 합니다. 이 파일이 부팅 때마다 좌/우 정보를 EEPROM에 기록합니다.

TRRS 케이블은 USB를 뽑은 상태에서만 꽂고 빼세요.

## 핀 배치 (PCB `Paikorea.kicad_pcb`에서 추출)

| 신호 | GPIO | | 신호 | GPIO |
| --- | --- | --- | --- | --- |
| col1 (바깥쪽 새끼) | GP4 | | row0 | GP5 |
| col2 | GP3 | | row1 | GP6 |
| col3 | GP2 | | row2 | GP7 |
| col4 | GP1 | | row3 (엄지열) | GP10 |
| col5 (안쪽 검지) | GP0 | | TRRS Data | GP11 |
| 트랙패드 SDA | GP8 | | 트랙패드 SCL | GP9 |

다이오드 방향은 COL2ROW입니다. 왼쪽(뒷면 조립)은 PCB에서 U2의 GP8/GP9가 연결되어 있지 않으니, 트랙패드 SDA→GP8, SCL→GP9, VDD→3V3, GND→GND로 직접 배선하세요. RDY/RST 핀은 쓰지 않습니다. 트랙패드가 없는 쪽은 펌웨어가 알아서 무시합니다.

## 기본 키맵 (Vial)

`keymaps/vial/keymap.c`에 들어 있습니다.

```
 ,----------------------------------.              ,----------------------------------.
 |   Q  |   W  |   E  |   R  |   T  |              |   Y  |   U  |   I  |   O  |   P  |
 |   A  |S/Ctl |D/Sft |F/Alt |   G  |   [패드]    |   H  |   J  |K/Sft |L/Ctl |   ;  |
 |Sft/Z |   X  |   C  |   V  |B/RAIS|   [패드]    |   N  |   M  |   ,  |   .  |   /  |
 | Ctrl |             |Enter |Space |LOWER |  |RAISE |Space | Bksp |             | RAlt |
 `------'             `--------------------'  `--------------------'             `------'
```

- **홈row 모드(탭댄스)**: S/D/F, K/L은 탭하면 글자, 누르고 있으면 Ctrl/Shift/Alt (F의 Alt만 500 ms, 나머지 130 ms). B는 누르고 있으면 RAISE, Enter 키도 탭댄스(TD0)입니다.
- **콤보**: N + M = B
- **LOWER**: 숫자 1–0, 방향키(왼손 ESDF 자리), 볼륨/재생, 오른손 숫자패드(1–6, 엄지 0), Tab, Del, 오른쪽 끝 한자
- **RAISE**: F1–F12(왼손), 기호(``' - = [ ] \ ` _ + { } |``), Esc, Bksp, Enter, 매크로 `M0` = Ctrl+Shift+Esc, `M1` = Win+Shift+S
- **LOWER + RAISE**: 비어 있음 (Vial에서 채워 쓰세요)

탭댄스·콤보·매크로는 Vial의 EEPROM 항목이라, EEPROM이 초기화될 때(새 펌웨어를 플래싱했을 때, `QK_CLEAR_EEPROM`/Bootmagic) 펌웨어가 위 기본값을 다시 써 넣습니다. Vial에서 바꾼 내용은 다음 초기화 전까지 유지됩니다.

기본 키맵에는 `QK_BOOT`가 없습니다. 부트로더는 **RESET을 빠르게 두 번** 누르거나 **BOOT를 누른 채 USB를 꽂아** 들어가세요. `DrgScrl`/`PadSwap`도 기본 키맵에는 없으니 필요하면 Vial의 User 탭에서 넣으세요.

Vial에서 모두 바꿀 수 있습니다. 처음 연결하면 잠금 해제를 요구할 수 있는데, **왼쪽 Q + 오른쪽 P를 함께 누르고 있으면** 풀립니다.

`keymaps/default/`(Vial 없는 테스트용 QMK)는 예전 키맵 그대로입니다.

## 트랙패드 동작

- 오른쪽 패드: 커서 이동 / 왼쪽 패드: 한 손가락 스크롤
- 한 손가락 탭 = 왼쪽 클릭, 두 손가락 탭 = 오른쪽 클릭, 두 손가락 드래그 = 스크롤, 탭 후 누르고 있기 = 드래그(텍스트 선택)
- `DrgScrl`(Vial의 User 탭): 누르고 있는 동안 양쪽 패드 모두 스크롤
- `PadSwap`: 커서/스크롤 패드를 서로 바꿈

### 방향이 맞지 않을 때

패드를 붙인 방향에 따라 축이 뒤집힐 수 있습니다. 처음 테스트한 뒤 `keyboards/paikorea/config.h`에서 필요한 줄의 주석을 풀고 다시 빌드하세요.

```c
// 왼쪽 패드
// #define POINTING_DEVICE_ROTATION_180
// #define POINTING_DEVICE_INVERT_X
// #define POINTING_DEVICE_INVERT_Y
// 오른쪽 패드
// #define POINTING_DEVICE_ROTATION_180_RIGHT
// #define POINTING_DEVICE_INVERT_X_RIGHT
// #define POINTING_DEVICE_INVERT_Y_RIGHT
```

스크롤 속도는 `PAIKOREA_SCROLL_DIVISOR`(클수록 느림), 방향은 `PAIKOREA_SCROLL_INVERT`로 조절합니다.

## 직접 빌드하기

```sh
git clone --depth 1 https://github.com/vial-kb/vial-qmk
cd vial-qmk && make git-submodule
cp -r ../Paikorea_firmware/keyboards/paikorea keyboards/
make paikorea:vial PAIKOREA_SIDE=left    # → paikorea_vial.uf2 (왼쪽용)
make paikorea:vial PAIKOREA_SIDE=right   # → paikorea_vial.uf2 (오른쪽용)
```

## 구조

```
keyboards/paikorea/
├── keyboard.json      매트릭스, 핀, 스플릿, 레이아웃
├── config.h           핸드니스, I2C, 트랙패드 설정
├── rules.mk           트랙패드 드라이버, 좌/우 빌드 옵션
├── halconf.h, mcuconf.h  RP2040 I2C0 활성화
├── paikorea.c/.h      트랙패드 스크롤/스왑 커스텀 키코드
└── keymaps/
    ├── default/       일반 QMK 키맵
    └── vial/          Vial 키맵 + vial.json
```

License: 이 레포의 소스는 MIT입니다. 빌드된 펌웨어는 QMK(GPL-2.0)와 함께 묶이므로 GPL을 따릅니다.
