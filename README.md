# MSPM0G3507 云台控制项目

## 项目简介

本项目基于 TI MSPM0G3507 微控制器开发的车车系统。

## 硬件平台

- **主控芯片**: TI MSPM0G3507
- **开发环境**: Keil MDK-ARM v6
- **SDK版本**: MSPM0 SDK 2.05.01.00

## 功能特性

- 跑车
- 双轴云台控制（俯仰/偏航）
- 视觉串口通信支持
- 屏幕显示
- 模式切换


### 视觉模块通讯
| 单片机->k230 |  | k230->单片机 |  |
|--------|------|------|------|
| 开启识别 | AA AA BB | 差值返回 | AA (16位x偏移值)(16位y偏移值)  BB |
| 结束识别 | AA FF BB | 例 | AA 00 00 00 00 BB |



## 项目结构

```
empty/
├── empty.c                 # 主程序文件
├── ti_msp_dl_config.h      # 系统配置头文件
├── gimbal/                 # 云台控制模块
│   ├── gimbal.h           # 云台控制头文件
│   ├── gimbal.c           # 云台控制实现
│   ├── ZDT_drive.h        # 电机驱动头文件
│   └── ZDT_drive.c        # 电机驱动实现
├── vision/                 # 视觉处理模块
│   ├── vision.h           # 视觉处理头文件
│   └── vision.c           # 视觉处理实现
├── time/                   # 时间处理模块
│   ├── time.h             # 时间处理头文件
│   └── time.c             # 时间处理实现
├── uart/                   # 串口通信模块
│   ├── uart.h             # 串口通信头文件
│   └── uart.c             # 串口通信实现
└── README.md               # 项目说明文档

```

![:FuckTI](https://count.getloli.com/@Xuan?name=Xuan&theme=rule34&padding=7&offset=0&align=top&scale=1&pixelated=1&darkmode=auto)

