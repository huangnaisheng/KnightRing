# ⚔️ CombatSystem 插件化 & Fab 上架路线图

> 目标：把 KnightRing（UeLearn）项目中的 GAS 战斗框架抽象为可复用的 **Runtime 插件**，打磨后上架 [Fab](https://www.fab.com)（Epic 新商城）。
> 状态：本文档基于项目源码与配置逐文件整理（2026-04 归档时点）。

---

## 0. 现状盘点

| 资产 | 现状 | 插件化处置 |
|---|---|---|
| `AMyCPPCharacterBase`（ASC 角色基类，Mixed 复制） | ✅ 可复用 | 改名 `ACombatCharacterBase` 进插件 |
| `UAttributeSetBase`（11 属性 + 回调判定） | ✅ 可复用 | 改名 `UCombatAttributeSet` 进插件 |
| `AWaveDirector`（波次刷怪 + Boss） | ✅ 可复用 | 保留名字进插件 `Director/` |
| `UMyBlueprintFunctionLibrary`（HitStop 顿帧） | ✅ 可复用 | 改名 `UCombatBlueprintLibrary` 进插件 |
| `UMyBlueprintFunctionLibrary`（ReadTxt/WriteTxt） | ⚠️ 与战斗无关 | 拆到 `CombatSystemUtils` 模块 |
| `UMyDownloader`（异步 HTTP 下载） | ⚠️ 与战斗无关 | 拆到 `CombatSystemUtils` 模块 |
| `AMyCharacterBase` / `AMyNetCharacterBase` / `AMyPlayerController` | ❌ 学习练习代码 | 留在示例工程，不进插件 |
| 54 个 GameplayTag（ini 配置） | ⚠️ 项目级配置 | 迁移为 **Native Gameplay Tags**（C++ 声明） |
| 能力 / 效果 / Cue 蓝图资产 | ⚠️ 引用商城资源 | Phase 2 用干净资源**重做**一套 demo |
| `Content/` 商城资产（Gladiator_Arena 等 9.3 GB） | ❌ 无再分发权 | **严禁**进入插件，一个字节都不能带 |

---

## Phase 1：代码插件化（约 1–2 周，纯 C++ 工作）

### 1.1 目标插件结构

```
Plugins/CombatSystem/
├── CombatSystem.uplugin
├── Source/
│   ├── CombatSystem/                        # Runtime 模块：战斗核心
│   │   ├── CombatSystem.Build.cs
│   │   ├── Public/
│   │   │   ├── CombatSystem.h
│   │   │   ├── Characters/CombatCharacterBase.h      # ← MyCPPCharacterBase
│   │   │   ├── Attributes/CombatAttributeSet.h       # ← AttributeSetBase
│   │   │   ├── Combat/CombatBlueprintLibrary.h       # ← HitStop 顿帧
│   │   │   └── Director/WaveDirector.h               # ← 波次刷怪
│   │   └── Private/  (同名 .cpp)
│   └── CombatSystemUtils/                   # Runtime 模块：通用工具（可选拆分）
│       ├── CombatSystemUtils.Build.cs
│       ├── Public/
│       │   ├── Download/AsyncDownloader.h            # ← MyDownloader
│       │   └── FileIO/FileLibrary.h                  # ← ReadTxt/WriteTxt
│       └── Private/
├── Config/                                  # 插件自身配置（如需）
├── Content/                                 # Phase 2 的干净 demo 内容（先留空）
└── README.md
```

### 1.2 类重命名映射表

| 旧类 | 新类 | 说明 |
|---|---|---|
| `AMyCPPCharacterBase` | `ACombatCharacterBase` | 保留 `IAbilitySystemInterface`、子对象创建、`PossessedBy/OnRep_PlayerState` 双入口初始化、Mixed 复制 |
| `UAttributeSetBase` | `UCombatAttributeSet` | 11 属性保留为「魂系示例属性集」；注释说明如何删减/新增属性；`PostGameplayEffectExecute` 的死亡/架势崩溃/升级判定保留并加注释 |
| `AWaveDirector` | `AWaveDirector` | 名字不变，移入 `Director/` |
| `UMyBlueprintFunctionLibrary` | `UCombatBlueprintLibrary` | 只保留 `ApplyHitStop`；文件读写移出 |
| `UMyDownloader` | `UAsyncDownloader` | 移入 Utils 模块 |
| — | `UCombatFileLibrary` | 收编 ReadTxt/WriteTxt |

### 1.3 改造清单（Checklist）

- [ ] 新建 `.uplugin`（`Modules` 声明 Runtime 两个模块；`EnabledByDefault: false` 留给用户启用）
- [ ] `CombatSystem.Build.cs` 依赖：`GameplayAbilities` / `GameplayTags` / `GameplayTasks` / `EnhancedInput` / `NavigationSystem`；`HTTP` 归 Utils 模块
- [ ] API 宏：`UELEARN_API` → `COMBATSYSTEM_API`（Utils 用 `COMBATSYSTEMUTILS_API`）
- [ ] include 路径：`UeLearn/...` → `CombatSystem/...`
- [ ] **54 个 GameplayTag 迁移为 Native Gameplay Tags**：`UE_DECLARE_GAMEPLAY_TAG_EXTERN` 统一声明 + 单一 `.cpp` 定义，编辑器仍可见可编辑（Lyra 同款做法）
- [ ] 源文件 GBK → UTF-8；删除注释掉的调试代码、"Fill out your copyright notice" 改为你的版权头
- [ ] 中文注释统一译为英文（插件面向全球用户），或保留双语
- [ ] 属性宏 `ATTRIBUTE_ACCESSORS` 保留，作为插件内公共头提供
- [ ] 示例工程：新建空白 C++ 工程启用插件，用引擎 Mannequin 验证编译与运行
- [ ] 编写插件 README：安装方式、快速上手、API 说明、版本支持表

### 1.4 验收标准

- [ ] 全新 UE 5.4 工程启用插件后**零警告编译通过**
- [ ] 示例角色（Mannequin）可受击 / 死亡 / 架势崩溃 / 升级
- [ ] 刷怪导演在空关卡可运行
- [ ] 无任何 `Content/` 商城资产引用

---

## Phase 2：干净 Demo 内容（约 2–4 周，需编辑器）

### 2.1 内容来源三原则

| 来源 | 用途 | 注意 |
|---|---|---|
| **自制** | 角色/武器白模、打击 VFX（Niagara）、HUD | 全部自建 |
| **引擎自带** | Mannequin 骨骼网格与第三人称动画、基础材质 | 一般允许用于 demo，以 Fab 审核规则为准 |
| **CC0 / 自购授权** | 打击音效、音乐（可选） | 保留授权凭证截图 |

> ⚠️ 现有蓝图（GA/GE/GC/HUD）都引用商城资产，**不可直接搬**，需在干净工程里按原逻辑重做一份。你的 54 标签词汇表（C++ 侧）可以直接复用——这是插件的灵魂。

### 2.2 Demo 必须演示的功能矩阵

- [ ] 架势条：打满 → 硬直 → 处决窗口 → 归零
- [ ] 弹反 / 防反 / 处决（含运镜）
- [ ] 喝药（百分比回血）、元素瓶
- [ ] 输入缓冲（连招与闪避预输入）
- [ ] 顿帧 HitStop
- [ ] 波次刷怪 + 简易 Boss（2–3 招即可）
- [ ] 升级三选一 HUD

### 2.3 授权自检表

- [ ] 每个资产可追溯来源（自制 / 引擎 / CC0 / 已购授权）
- [ ] 字体、图标、UI 素材版权清晰
- [ ] 音效/音乐授权凭证存档

---

## Phase 3：Fab 上架（流程约 2–4 周）

### 3.1 卖家入驻

1. [fab.com](https://www.fab.com) 注册并申请成为卖家（Publisher）
2. 签署卖家协议，填写**税务信息**（个人：W-8BEN 或增值税登记）与收款方式
3. 分成：**88% 归你 / 12% Epic**（上架后按月结算）

### 3.2 产品包装

- 产品名（建议 `CombatSystem` 或更有辨识度的名字）+ 图标
- 截图 ≥ 5 张、演示视频 1–2 分钟（重点拍架势/弹反/处决/输入缓冲）
- 英文产品描述：卖点、功能列表、技术信息（模块依赖、支持版本、蓝图/C++）
- 文档：Getting Started、API 参考、更新日志、支持渠道（论坛帖 / 邮件）
- 定价建议：**首版免费**，攒下载量与评价；成熟后拆分 Pro 付费版（如联机、更多武器类型）

### 3.3 提交与审核

- Code Plugin 走**代码审核**：编译检查、Epic 编码规范、无第三方代码
- 内容审核：授权合规（重点核查资产来源）
- 被拒是常态：按审核反馈修改后重新提交

### 3.4 风险与对策

| 风险 | 对策 |
|---|---|
| 审核被拒（授权/规范） | 按反馈逐条修改；Phase 2 的自检表提前规避 |
| 与现有战斗插件竞争 | 主打差异化：只狼式架势+弹反+处决词汇表、输入缓冲、顿帧手感 |
| 版本维护成本 | 明示支持版本范围（如 5.3–5.5），季度更新 |
| 售后压力 | 免费插件约定「尽力支持」，建 FAQ 帖 |

---

## 4. 总时间线与里程碑

| 阶段 | 周期 | 交付物 | 里程碑 |
|---|---|---|---|
| Phase 1 | 1–2 周 | CombatSystem 插件（编译通过）+ 示例工程 | **M1** 插件可复用 |
| Phase 2 | 2–4 周 | 干净 demo 内容 + 授权自检通过 | **M2** Demo 可玩 |
| Phase 3 | 2–4 周 | 卖家账号 + 产品页 + 审核通过 | **M3** 提交 / **M4** 上架 |

预计总量：**5–10 周**（课余/业余时间约 2–3 个月）。

---

## 5. 附录：核心卖点一句话

> A GAS-powered, Sekiro-style melee combat framework for UE 5.4 — posture system, parry/counter/execution with cinematic camera, input buffering, hit-stop feel, wave-based AI director, and a 54-tag combat vocabulary out of the box.

（上架前记得把这句话变成产品页的第一段。）
