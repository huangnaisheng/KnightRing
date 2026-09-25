# ⚔️ KnightRing · UeLearn

> UE 5.4 · C++ / Blueprint · GAS（Gameplay Ability System）魂系战斗 Demo

![UE](https://img.shields.io/badge/Unreal_Engine-5.4-313131?logo=unrealengine&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?logo=cplusplus&logoColor=white)
![GAS](https://img.shields.io/badge/Gameplay_Ability_System-GAS-8B5CF6)
![EnhancedInput](https://img.shields.io/badge/Enhanced_Input-0078D4)
![状态](https://img.shields.io/badge/status-学习Demo-brightgreen)
[![完整工程备份](https://img.shields.io/badge/完整工程备份-百度网盘·提取码kcgm-0066CC)](https://pan.baidu.com/s/1EjpiQiZTGHKf1InNfHM_GQ?pwd=kcgm)

一个拆解 **《只狼》战斗系统** 的 Unreal Engine 学习项目：用 GAS 实现架势条、弹反/防反、处决与运镜、输入缓冲、全局顿帧、AI 立回（EQS）、Boss 战、掉落物与任务系统。

---

## 🗺️ 技术栈思维导图

![技术栈思维导图](Docs/images/tech-stack.png)

## ⚔️ GAS 架构

![GAS 战斗数据流管线](Docs/images/gas-pipeline.png)

<details>
<summary>📌 展开查看：核心组件结构 & GameplayTag 体系</summary>
<br>

![GAS 核心组件与类结构](Docs/images/gas-structure.png)

![GameplayTag 标签体系](Docs/images/gas-tags.png)

</details>

> 🖱️ 交互版（可缩放 / 下载 SVG 矢量图）：[Docs/TechStack-GAS-MindMap.html](Docs/TechStack-GAS-MindMap.html)

## 🎮 功能清单

**战斗核心**
- 架势条（Posture）：打满触发硬直 → 处决窗口，可恢复
- 弹反（Parry）/ 防反（Counter）/ 处决（Execute）+ 处决运镜
- 喝药（DrinkPotion，百分比回血）、元素瓶（EstusCount）
- 连招（Combo）与攻击重置、输入缓冲（Input Buffer）预输入
- 全局顿帧 HitStop（C++ Lambda 实现，CustomTimeDilation）

**敌人与 AI**
- EQS_Starfe 立回走位、AI 弹反玩家并反击、AI 处决玩家
- 波次刷怪 WaveDirector（NavMesh 动态生成随机刷怪点）

**Boss 战**
- Boss 5 招（GA_BossAttack）、Boss 大血条 UI、定制生成（SpawnBoss）
- 受击覆盖修复（Retrigger Instanced Ability）

**成长与系统**
- 经验条（EXP）、升级三选一面板（Event.LevelUp 驱动）
- 掉落物系统、任务系统、死亡 UI 与重来按钮
- 网络预留：ASC 复制（Mixed 模式）

## 🗂️ 目录结构

```
KnightRing/
├── Source/UeLearn/                        # C++ 代码
│   ├── GameplayAbilitySystem/             # GAS：ASC 角色 + 11 属性 AttributeSet
│   │   ├── Characters/MyCPPCharacterBase  # IAbilitySystemInterface 实现
│   │   └── AttributeSets/AttributeSetBase # 生命/精力/架势/瓶子/经验
│   ├── Characters/MyCharacterBase         # 第三人称角色（Enhanced Input）
│   ├── WaveDirector                       # 波次刷怪导演（NavMesh）
│   ├── MyDownloader                       # 异步 HTTP 下载节点
│   └── MyBlueprintFunctionLibrary         # 顿帧 HitStop + 本地读写
├── Config/                                # 引擎配置 + 54 个 GameplayTag
├── Docs/                                  # 技术栈 & GAS 架构图（含交互版）
└── UeLearn.uproject                       # UE 5.4 项目文件
```

## 📅 开发时间线

| 日期 | 进度 |
|---|---|
| 3.14 – 3.21 | 深入学习 GAS：改写底层 Tag、拆解只狼战斗系统、改写第三人称模板 |
| 3.21 – 3.22 | UE C++：Lambda 实现全局顿帧 HitStop |
| 3.23 | 死亡判定 GA、处决运镜、修 UI Bug、AI 弹反玩家并反击 |
| 3.24 | 架势条恢复机制与 UI、喝药、AI 优化 |
| 3.25 | 地图场景、刷怪功能、改写 EQS_Starfe 让 AI 流畅立回 |
| 3.26 | 掉落物系统、任务系统、刷怪优化 |
| 3.27 | Boss 战、升级三选一面板、回血改百分比、动画与素材 |
| 3.28 | AI 处决玩家、Boss 动画、输入缓冲、Retrigger Instanced Ability 修受击覆盖 |
| 3.29 | 改写 SpawnBoss、Boss 战手感、Boss 大血条、GA_BossAttack |
| 3.30 | Boss 5 招、换地图、音乐动画、死亡 UI 与重来按钮 |
| 3.31 – 4.1 | 输入缓冲收尾、答辩 PPT、血条 UI 与经验条 |

## 🚀 恢复完整工程

GitHub 仓库只包含**代码与配置**。完整美术资源（约 9.3 GB）与第三方插件在网盘备份包 `KnightRing_FullBackup.7z` 中：

1. 克隆仓库：
   ```bash
   git clone https://github.com/huangnaisheng/KnightRing.git
   ```
2. 下载完整工程备份（`KnightRing_FullBackup.7z`，约 7.8 GB）并解压，把 `Content/` 与 `Plugins/` 复制到项目根目录：
   - 🔗 链接：https://pan.baidu.com/s/1EjpiQiZTGHKf1InNfHM_GQ?pwd=kcgm
   - 🔑 提取码：`kcgm`
3. 安装 **UE 5.4**，双击 `UeLearn.uproject` 打开（首次会提示重新编译）

## 🧩 第三方插件来源

| 插件 | 来源 |
|---|---|
| VRM4U | https://github.com/ruyo/VRM4U |
| SwitchLanguage | Epic Fab 商城 |
| KawaiiPhysics / SPCRJointDynamics | GitHub 开源插件 |

## ⚖️ 许可提醒

`Content/` 中的市场资源（Fab / Epic 商城资产）仅供个人学习使用，请勿再分发。

## 📌 下一步

计划把战斗框架抽象为独立插件并上架 Fab 商城，完整路线图见 [Docs/PluginRoadmap.md](Docs/PluginRoadmap.md)。
