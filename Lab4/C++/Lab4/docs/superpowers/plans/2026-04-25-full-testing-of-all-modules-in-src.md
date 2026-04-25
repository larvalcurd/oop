
# Full Testing of All Modules in src Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Ensure comprehensive, automated, and reliable testing for all modules in the `src` directory.

**Architecture:** Each module in `src` (shapes, app, canvas) is covered by focused unit and integration tests in the `tests` directory. Tests use GoogleTest. Each test file targets a single module/class. All public methods and edge cases are covered. Integration tests validate module interactions.

**Tech Stack:** C++, GoogleTest, CMake

---

### Task 1: Ensure All Shape Classes Are Fully Tested

**Files:**
- Modify: `tests/shapes/CLineSegmentTests.cpp`
- Modify: `tests/shapes/CRectangleTests.cpp`
- Modify: `tests/shapes/CTriangleTests.cpp`
- Modify: `tests/shapes/CCircleTests.cpp`

- [ ] **Step 1: Review and expand tests for all public methods and edge cases**
- [ ] **Step 2: Add missing tests for invalid/edge input (e.g., zero/negative dimensions, color values, collinear points for triangles, etc.)**
- [ ] **Step 3: Run tests and verify all pass**
- [ ] **Step 4: Commit**

### Task 2: Ensure ShapeManager and ShapeFactory Are Fully Tested

**Files:**
- Modify: `tests/app/ShapeManagerTests.cpp`
- Modify: `tests/app/CShapeFactoryTests.cpp`

- [ ] **Step 1: Review and expand tests for all public methods and edge cases**
- [ ] **Step 2: Add missing tests for invalid/edge input (e.g., null shapes, invalid shape descriptions, etc.)**
- [ ] **Step 3: Run tests and verify all pass**
- [ ] **Step 4: Commit**

### Task 3: Ensure Canvas Module Is Fully Tested

**Files:**
- Modify: `tests/canvas/CCanvasTests.cpp`
- Modify: `tests/canvas/ShapeDrawTests.cpp`
- Modify: `tests/canvas/ShapeManagerDrawOrderTests.cpp`

- [ ] **Step 1: Review and expand tests for all public methods and edge cases**
- [ ] **Step 2: Add/expand tests for drawing primitives, order, and error handling**
- [ ] **Step 3: Run tests and verify all pass**
- [ ] **Step 4: Commit**

### Task 4: Integration and Regression Testing

**Files:**
- Modify: `tests/app/ShapeManagerTests.cpp` (integration)
- Modify: `tests/app/CShapeFactoryTests.cpp` (integration)
- Modify: `tests/canvas/ShapeDrawTests.cpp` (integration)

- [ ] **Step 1: Add/expand integration tests covering interactions between modules (e.g., creating shapes, adding to manager, drawing on canvas)**
- [ ] **Step 2: Add regression tests for previously fixed bugs (if any)**
- [ ] **Step 3: Run all tests and verify all pass**
- [ ] **Step 4: Commit**

### Task 5: Test Coverage and Documentation

**Files:**
- Create: `docs/superpowers/plans/2026-04-25-full-testing-of-all-modules-in-src.md`

- [ ] **Step 1: Document test coverage for each module and class**
- [ ] **Step 2: List any known gaps or limitations**
- [ ] **Step 3: Commit**
