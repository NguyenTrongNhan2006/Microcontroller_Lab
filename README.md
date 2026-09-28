# HCMUT Microcontroller Lab Portfolio (ĐHBK TP.HCM)

**Trường Đại học Bách Khoa - ĐHQG TP.HCM**  
**Khoa Khoa Học và Kỹ Thuật Máy Tính - Bộ Môn Kỹ Thuật Máy Tính**  
**Môn học**: Vi điều khiển / Thực tập Vi điều khiển (Microcontroller)  
**Giảng viên**: TS. Lê Trọng Nhân  
**Sinh viên thực hiện**: Nguyễn Trọng Nhân ([@NguyenTrongNhan2006](https://github.com/NguyenTrongNhan2006))  

---

## 📌 Giới Thiệu Khóa Học
Kho lưu trữ này chứa toàn bộ tài liệu học tập, mã nguồn C (chuẩn thư viện STM32 HAL), file mô phỏng sơ đồ nguyên lý Proteus và các báo cáo thực hành cho chuỗi 5 bài thí nghiệm (Labs) của môn học **Vi điều khiển**:

| Lab | Tên bài thí nghiệm | Trọng tâm kiến thức | Trạng thái |
|:---:|---|---|:---:|
| **[Lab 1](Lab1_LED_Animations/)** | **LED Animations** | GPIO Output, Active LOW, Đèn giao thông, LED 7 đoạn, Đồng hồ 12 LED | **Hoàn thành khung & hướng dẫn** |
| **[Lab 2](Lab2_Timer_Interrupt/)** | **Timer & Interrupts** | Hardware Timer, Ngắt định thời (UIF), Software Timer non-blocking | Source 10 bài + HEX; đã kiểm thử logic |
| **[Lab 3](Lab3_FSM_Traffic_Light/)** | **Finite State Machine & Buttons** | Thiết kế FSM, Chống rung nút bấm (Debounce), Đèn giao thông đa chế độ | Dự kiến |
| **[Lab 4](Lab4_UART_Communication/)** | **UART Communication & Parser** | Giao thức truyền thông nối tiếp, Ngắt UART RX/TX, Bộ đệm vòng (Ring Buffer) | Dự kiến |
| **[Lab 5](Lab5_ADC_and_Sensors/)** | **ADC, Sensors & PWM** | Bộ chuyển đổi tương tự-số 12-bit ADC, Cảm biến, Điều chế độ rộng xung PWM | Dự kiến |

---

## 🛠️ Công Cụ Phát Triển & Mô Phỏng
- **Phần cứng mục tiêu**: Vi điều khiển **STM32F103C6** (ARM Cortex-M3, 72 MHz, 32KB Flash, 10KB SRAM).
- **Môi trường lập trình (IDE)**: **STM32CubeIDE** (phiên bản khuyến nghị 1.7.0 trở lên).
- **Môi trường mô phỏng mạch**: **Proteus Professional 8.10 SP0**.

---

## 🌟 Điểm Nhấn Lab 1: LED Animations

Lab 1 bao gồm trọn vẹn 10 bài tập được tổ chức gọn gàng, có đầy đủ hướng dẫn lý thuyết, sơ đồ nối dây Proteus và mã nguồn mẫu chứa `// TODO`:

```
Lab1_LED_Animations/
├── Docs/                                    # Hướng dẫn chi tiết từng bước theo giáo trình
│   ├── 01_STM32CubeIDE_Setup.md             # Tạo project, cấu hình GPIO, xuất file Hex
│   ├── 02_Proteus_Simulation.md             # Vẽ mạch, cấp nguồn 3.3V, nối VDDA/VSSA, nạp Hex
│   └── 03_Report_Guide.md                   # Hướng dẫn nộp Report 1 (Sơ đồ) & Report 2 (Mã nguồn)
├── Source_Code/                             # Toàn bộ mã nguồn C của 10 bài tập
│   ├── Inc/
│   │   ├── main.h                           # Header chính và định nghĩa GPIO
│   │   └── exercises.h                      # Khai báo nguyên mẫu hàm của 10 bài
│   └── Src/
│       ├── main.c                           # File main STM32 HAL (chọn gọi exercise để chạy)
│       ├── exercise1.c .. exercise10.c      # Khung sườn từng bài tập (chứa // TODO)
├── Proteus/
│   ├── README.md                            # Hướng dẫn nạp file hex và chạy mô phỏng
│   └── schematics/                          # Nơi chèn ảnh sơ đồ Proteus cho từng bài tập
│       ├── ex1_schematic.png                # Ảnh sơ đồ bài 1 (2 LED luân phiên)
│       ├── ex2_schematic.png                # Ảnh sơ đồ bài 2 (Đèn giao thông đơn)
│       ├── ex3_schematic.png                # Ảnh sơ đồ bài 3 (Đèn giao thông 4 ngã)
│       ├── ex4_schematic.png                # Ảnh sơ đồ bài 4 (LED 7 đoạn Anode chung)
│       ├── ex5_schematic.png                # Ảnh sơ đồ bài 5 (Đèn giao thông + đếm ngược 7-SEG)
│       ├── ex6_schematic.png                # Ảnh sơ đồ bài 6 (Đồng hồ 12 LED)
│       └── ex10_schematic.png               # Ảnh sơ đồ bài 10 (Đồng hồ kim hoàn chỉnh)
└── README.md                                # Tài liệu chi tiết của riêng Lab 1
```

👉 **Đọc hướng dẫn chi tiết toàn bộ Lab 1 tại**: [**Lab1_LED_Animations/README.md**](Lab1_LED_Animations/README.md)

---

## 🚀 Cách Bắt Đầu Sử Dụng
1. **Clone repository về máy**:
   ```bash
   git clone https://github.com/NguyenTrongNhan2006/Microcontroller_Lab.git
   ```
2. **Mở STM32CubeIDE**:
   - Mở file `.c` tương ứng trong `Lab1_LED_Animations/Source_Code/Src/`.
   - Viết phần giải thuật vào các khối `// TODO`.
   - Bật xuất Intel Hex và nhấn `Ctrl + B` để biên dịch.
3. **Mô phỏng trên Proteus**:
   - Mở Proteus với quyền Administrator.
   - Nạp file `.hex` vào chip STM32F103C6 và nhấn nút Play để quan sát kết quả.
   - Chụp ảnh sơ đồ lưu đè vào thư mục `Lab1_LED_Animations/Proteus/schematics/`.
