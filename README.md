# 🎨✨ Node-Based Image Processor

A powerful and extensible **node-based image editing** desktop application built with **C++**, **Qt**, and **OpenCV**. Inspired by tools like **Substance Designer**, this app allows users to process images using a visual node editor.

---

## 📸 Project Highlights

- 🔧 **Modular Node System** – Drag, drop, and connect nodes visually
- ⚙️ **Real-Time Processing** – Immediate feedback when adjusting parameters
- 🖼️ **Image I/O** – Load and save images with format/quality options
- 🎚️ **Parameter Control Panel** – Adjust settings per node
- 💾 **Built with Qt & OpenCV** – High-performance and cross-platform

---

## 🧱 Implemented Nodes

| ✅ Node Name               | 🌟 Functionality |
|---------------------------|------------------|
| 📂 **Image Input**         | Load JPG, PNG, BMP + show metadata |
| 💡 **Brightness/Contrast** | Adjustable sliders with reset |
| 🌀 **Gaussian Blur**       | Blur with radius + kernel preview |
| 🧪 **Threshold**           | Binary, Adaptive, Otsu methods |
| ⚡ **Edge Detection**      | Sobel and Canny with overlays |
| 🎨 **Color Splitter**      | Break into R/G/B channels |
| 🧷 **Blend**               | 5 Blend modes + mix slider |
| 🎲 **Noise Generator**     | Perlin, Simplex, Worley |
| 🧠 **Convolution Filter**  | Custom 3x3/5x5 kernels |
| 💾 **Output Node**         | Save image with format/quality |

---

## 🚀 How to Build

> 🔧 Prerequisites: C++17+, CMake, Qt (>=5.15), OpenCV

```bash
git clone https://github.com/yourusername/node-based-image-processor.git
cd node-based-image-processor
mkdir build && cd build
cmake ..
make
./NodeImageProcessor
