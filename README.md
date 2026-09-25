# KnightRing（UeLearn）

一个基于 **Unreal Engine 5.4** 的 GAS（Gameplay Ability System）学习项目。

## 仓库说明

GitHub 仓库只包含**代码和配置**（约几十 MB）：

- `Source/` —— C++ 代码（GAS Demo）
- `Config/` —— 引擎与项目配置
- `UeLearn.uproject` —— 项目文件（UE 5.4）

**不包含**（体积过大，放在网盘备份包 `KnightRing_FullBackup.7z` 里）：

- `Content/` —— 全部美术资源（约 9.3 GB）
- `Plugins/` —— 第三方插件（VRM4U、KawaiiPhysics、SPCRJointDynamics、SwitchLanguage 等）

## 如何恢复完整工程

1. 克隆本仓库：
   ```bash
   git clone https://github.com/huangnaisheng/KnightRing.git
   ```
2. 下载网盘备份包 `KnightRing_FullBackup.7z` 并解压。
3. 把解压出来的 `Content/` 和 `Plugins/` 两个文件夹复制到项目根目录。
4. 用 Epic Games Launcher 确认已安装 **UE 5.4**，双击 `UeLearn.uproject` 打开即可（首次会提示重新编译）。

## 第三方插件来源

| 插件 | 来源 |
|---|---|
| VRM4U | https://github.com/ruyo/VRM4U |
| SwitchLanguage | Epic Fab 商城 |
| KawaiiPhysics | GitHub 开源插件 |
| SPCRJointDynamics | GitHub 开源插件 |

## 许可提醒

`Content/` 中的市场资源（Fab/Epic 商城资产）仅供个人学习使用，请勿再分发。
