# Hướng Dẫn Chi Tiết Cấu Hình STM32CubeIDE (Theo Lab Manual)

Tài liệu này tổng hợp toàn bộ các bước cấu hình và lập trình trên **STM32CubeIDE (phiên bản 1.7.0+)** dựa trên hướng dẫn chính thức của Thầy Lê Trọng Nhân (Bộ môn Kỹ thuật Máy tính - ĐHBK TP.HCM).

---

## Bước 1: Tạo Project Mới
1. Mở phần mềm **STM32CubeIDE**.
2. Trên thanh menu, chọn `File` -> `New` -> `STM32 Project`.
3. Chờ phần mềm cập nhật dữ liệu vi điều khiển (với lần đầu khởi động sẽ tải một số package).

## Bước 2: Chọn Vi Điều Khiển Target
1. Trong ô tìm kiếm `Part Number`, gõ: `STM32F103C6`.
2. Chọn dòng vi điều khiển `STM32F103C6` (gói LQFP48 hoặc UFQFPN48, Cortex-M3, 72 MHz).
3. Nhấn **Next**.

## Bước 3: Đặt Tên Project và Đường Dẫn
1. **Project Name**: Đặt tên (ví dụ `Led_Animations` hoặc `Microcontroller_Lab1`).
2. **Location**: Chọn đường dẫn lưu trữ.
   > **Lưu ý quan trọng**: Đường dẫn thư mục **tuyệt đối không được chứa khoảng trắng (space)** hoặc ký tự có dấu tiếng Việt (ví dụ `D:\BKU_Lab\Lab1`, tránh `D:\Bai tap\`).
3. **Targeted Language**: Chọn `C`.
4. **Targeted Binary Type**: `Executable`.
5. **Targeted Project Type**: Chọn bắt buộc là `STM32Cube`. Nhấn **Finish**.
6. Giữ phiên bản firmware mặc định (e.g. `STM32Cube FW_F1 V1.8.4`), nhấn **Finish**.

## Bước 4: Cấu Hình Chân GPIO Trên Pinout & Configuration (.ioc)
1. Giao diện cấu hình chip STM32F103C6 hiện ra.
2. Tìm chân **PA5**: Click chuột trái vào chân `PA5` -> Chọn `GPIO_Output`.
3. Đặt nhãn cho chân: Click chuột phải vào chân `PA5` -> Chọn `Enter User Label` -> Gõ `LED_RED`.
4. Làm tương tự cho các chân khác:
   - `PA6` -> `GPIO_Output` (Label: `LED_YELLOW`)
   - `PA7` -> `GPIO_Output` (Label: `LED_GREEN`)
   - `PA4` đến `PA15` -> `GPIO_Output` (Dùng cho 12 LED đồng hồ kim)
   - `PB0` đến `PB6` -> `GPIO_Output` (Dùng cho LED 7 đoạn Anode chung `7SEG-COM-ANODE`)
5. Nhấn `Ctrl + S` để lưu cấu hình. Chọn **Yes** khi được hỏi sinh mã nguồn tự động (`Do you want to generate Code?`).

## Bước 5: Viết Mã Nguồn Trong main.c
> **Quy tắc cốt lõi**: Luôn viết code người dùng nằm giữa các cặp comment `/* USER CODE BEGIN ... */` và `/* USER CODE END ... */`. Nếu viết ngoài khu vực này, mỗi khi chỉnh sửa cấu hình `.ioc` và lưu lại, mã nguồn sẽ bị xóa hoàn toàn.

Vị trí viết trong vòng lặp vô hạn `while (1)`:
```c
/* USER CODE BEGIN WHILE */
while (1)
{
    /* USER CODE END WHILE */

    // Chạy bài tập mong muốn:
    // exercise1_run();

    /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
```

### Các hàm HAL cơ bản:
- Đảo trạng thái chân:
  ```c
  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
  ```
- Ghi mức logic (Active LOW: mức RESET = 0V để sáng LED cực âm):
  ```c
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET); // BẬT LED
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);   // TẮT LED
  ```
- Tạo độ trễ:
  ```c
  HAL_Delay(1000); // Trễ 1000 ms (1 giây)
  ```

## Bước 6: Cấu Hình Sinh File Intel HEX Cho Proteus
1. Chuột phải vào tên Project trong Project Explorer -> Chọn `Properties`.
2. Chọn `C/C++ Build` -> `Settings`.
3. Chọn tab `Tool Settings` -> Chọn mục `MCU Post build outputs`.
4. Tích chọn vào ô: **Convert to Intel Hex file (-O ihex)**.
5. Nhấn `Apply and Close`.

## Bước 7: Biên Dịch Project (Build)
1. Nhấn tổ hợp phím `Ctrl + B` (hoặc vào menu `Project` -> `Build Project`).
2. Quan sát cửa sổ `Console` ở dưới cùng màn hình.
3. Khi biên dịch thành công: `Build Finished. 0 errors, 0 warnings`.
4. File `.hex` sẽ được tạo ra tại thư mục `Debug/` của project (ví dụ: `Debug/Microcontroller_Lab1.hex`). File này sẽ được nạp vào Proteus.
