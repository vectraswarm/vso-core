# VectraSwarm OS — vso-core

> The first open, EU-native operating system for secure autonomous drone swarms.

[![License](https://img.shields.io/badge/license-Apache%202.0-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/status-pre--alpha-orange.svg)]()
[![EXIST](https://img.shields.io/badge/funded-EXIST--Forschungstransfer-blue.svg)]()

---

## What is VSO?

VectraSwarm OS (VSO) is a hardware-agnostic, open-source operating system for coordinated autonomous drone swarms — built for security, resilience, and edge-AI inference without cloud dependency.

Think of it as **Android for drone swarms**: a standardized platform that runs on any drone hardware, with a secure swarm coordination layer on top.

### Key properties

- **Zero-Trust Security** — MAVLink v2 + MAVSEC (HMAC-SHA256), WireGuard, TEE/StrongBox
- **Decentralized Mesh** — WiFi Aware NAN, no ground station required
- **Byzantine Fault Tolerant** — swarm stays operational with up to 33% node failure
- **Hardware-Agnostic** — HAL abstraction (~200 lines C++) runs on any drone hardware
- **Edge AI** — on-device inference via ONNX/TensorRT/Hailo-8L, no cloud
- **EU-Native** — SORA/SAIL compliant, EU AI Act ready

---

## Architecture

```
┌─────────────────────────────────────────┐
│          VSO Application Layer          │
│     (Fleet Registry, Mission Logic)     │
├─────────────────────────────────────────┤
│           Edge AI Layer                 │
│    (YOLOv8-Nano, ONNX, Hailo-8L)        │
├─────────────────────────────────────────┤
│         Security Core (Rust)            │
│  (MAVSEC, WireGuard, BFT Consensus)     │
├─────────────────────────────────────────┤
│      Android AOSP + PREEMPT-RT          │
│        (Companion Computer)             │
├──────────────┬──────────────────────────┤
│  VSO HAL     │   PX4 Flight Controller  │
│  (~200 C++)  │   (STM32, MAVLink v2)    │
└──────────────┴──────────────────────────┘
         Any Drone Hardware
```

---

## Repository Structure

```
vso-core/
├── security-core/     # Rust: MAVSEC, BFT consensus, WireGuard integration
├── hal/               # C++: Hardware Abstraction Layer for OEM drone hardware
├── mesh/              # WiFi Aware NAN mesh, peer discovery
├── edge-ai/           # ONNX inference pipeline, Hailo-8L integration
├── docs/              # Architecture docs, API specs, safety documentation
└── scripts/           # Setup, build, and test scripts
```

---

## Validated PoC Results

| Component | Test Environment | Result |
|---|---|---|
| MAVSEC signing | STM32F7, n=1,000 packets | **0.8 ms overhead** |
| WireGuard tunnel | Two Linux hosts | **RTT 1.4 ms** |
| Android TEE/StrongBox | Pixel 7 | Key generation confirmed |
| 2-drone mesh | Android + PX4/STM32 | P2P connectivity established |

---

## Getting Started

### Prerequisites

```bash
# Clone the repo
git clone https://github.com/vectraswarm/vso-core.git
cd vso-core

# PX4 SITL (software simulation — no hardware needed)
git clone https://github.com/PX4/PX4-Autopilot --recursive
cd PX4-Autopilot && make px4_sitl gazebo
```

### Rust Security Core

```bash
cd security-core
cargo build
cargo test
```

---

## Roadmap

| Phase | Milestone | Status |
|---|---|---|
| PoC Month 1–2 | Security stack on COTS hardware | 🔄 In progress |
| PoC Month 3–4 | 3-node BFT mesh, WiFi Aware NAN | ⬜ Planned |
| PoC Month 5–6 | Edge AI integration (YOLOv8 + Hailo) | ⬜ Planned |
| Phase 2 | 20-drone field test, SORA certification | ⬜ Planned |

---

## Contributing

VSO is built under the EXIST-Forschungstransfer program in collaboration with the **Institut für Flugmechanik und Flugregelung (IFR), Universität Stuttgart** (Prof. Dr. Aamir Ahmad).

We are currently forming the founding team. If you are interested in contributing or joining:

- 📧 info@vectraswarm.com
- 🌐 [vectraswarm.com](https://vectraswarm.com)
- 💼 [linkedin.com/in/vectraswarm](https://linkedin.com/in/vectraswarm)

---

## License

VSO Core is released under the **Apache License 2.0** — free to use, modify, and distribute.
Enterprise components (Fleet Registry, KMS, audit tools) are proprietary.

See [LICENSE](LICENSE) for details.

---

*VectraSwarm — The Android of Drone Swarms*
