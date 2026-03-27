#!/bin/bash
# VectraSwarm OS — Developer Setup Script
# Run this once to set up your development environment

set -e

echo "=================================="
echo " VectraSwarm OS — Dev Setup"
echo "=================================="

# 1. Rust toolchain
echo "[1/5] Installing Rust..."
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source ~/.cargo/env
rustup target add thumbv7em-none-eabihf  # STM32 target

# 2. PX4 SITL dependencies
echo "[2/5] Installing PX4 SITL dependencies..."
sudo apt-get update -q
sudo apt-get install -y git cmake python3-pip ninja-build exiftool

# 3. PX4 Autopilot
echo "[3/5] Cloning PX4 Autopilot..."
if [ ! -d "PX4-Autopilot" ]; then
    git clone https://github.com/PX4/PX4-Autopilot --recursive --depth=1
fi

# 4. Python deps for Edge AI
echo "[4/5] Installing Python dependencies..."
pip3 install ultralytics onnxruntime flwr --quiet

# 5. Verify
echo "[5/5] Verifying setup..."
rustc --version
python3 -c "import ultralytics; print('YOLOv8 OK')"
python3 -c "import flwr; print('Flower FL OK')"

echo ""
echo "=================================="
echo " Setup complete!"
echo " Next step: cd PX4-Autopilot && make px4_sitl gazebo"
echo "=================================="
