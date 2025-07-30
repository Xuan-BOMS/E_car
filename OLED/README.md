# OLED驱动说明

本目录包含OLED SSD1306显示器的硬件I2C驱动程序。

## 文件说明

### 推荐使用的文件：
- **oled_hw_i2c.h** - 硬件I2C版本的OLED驱动头文件（简化版）
- **oled_hw_i2c.c** - 硬件I2C版本的OLED驱动实现（简化版）

### 原始模板文件：
- **oled_hardware_i2c.h** - SDK提供的硬件I2C模板头文件
- **oled_hardware_i2c.c** - SDK提供的硬件I2C模板实现

### 字体文件：
- **oledfont.h** - ASCII字符和汉字字体数据

## 使用方法

1. **包含头文件**：
   ```c
   #include "OLED/oled_hw_i2c.h"
   ```

2. **初始化OLED**：
   ```c
   OLED_Init();
   ```

3. **基本显示操作**：
   ```c
   OLED_Clear();                                    // 清屏
   OLED_ShowString(0, 0, (uint8_t*)"Hello", 16);   // 显示字符串
   OLED_ShowNum(0, 2, 123, 3, 16);                 // 显示数字
   OLED_ShowChar(0, 4, 'A', 16);                   // 显示字符
   ```

## 配置要求

使用硬件I2C驱动需要在SysConfig中配置以下内容：

1. **I2C模块配置**：
   - 实例名称：I2C_OLED
   - 频率：400kHz（标准模式）
   - 地址：0x3C（OLED设备地址）

2. **引脚配置**：
   - SCL引脚：需要配置为I2C功能
   - SDA引脚：需要配置为I2C功能

3. **必需的宏定义**（在ti_msp_dl_config.h中）：
   ```c
   #define I2C_OLED_INST                     // I2C实例
   #define GPIO_I2C_OLED_SCL_PORT           // SCL端口
   #define GPIO_I2C_OLED_SCL_PIN            // SCL引脚
   #define GPIO_I2C_OLED_SDA_PORT           // SDA端口  
   #define GPIO_I2C_OLED_SDA_PIN            // SDA引脚
   #define GPIO_I2C_OLED_IOMUX_SCL          // SCL复用配置
   #define GPIO_I2C_OLED_IOMUX_SDA          // SDA复用配置
   #define GPIO_I2C_OLED_IOMUX_SCL_FUNC     // SCL功能配置
   #define GPIO_I2C_OLED_IOMUX_SDA_FUNC     // SDA功能配置
   ```

## 优势

相比软件I2C实现，硬件I2C具有以下优势：

- **更高的效率**：硬件处理I2C协议，CPU占用更少
- **更稳定的通信**：硬件时序控制更精确
- **错误处理**：支持总线状态检测和错误恢复
- **更快的速度**：可以达到400kHz的通信速度

## 示例

详细的使用示例请参考根目录下的 `oled_example.c` 文件。

## 注意事项

1. 使用前必须先配置SysConfig
2. 确保I2C引脚没有被其他功能占用
3. OLED电源电压应为3.3V
4. 如果遇到I2C总线卡死，可以调用 `oled_i2c_sda_unlock()` 函数恢复
