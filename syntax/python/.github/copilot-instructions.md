# AI Coding Instructions for Python Study Project

## Project Overview

This is an educational Python study codebase organized by weekly exercises. It demonstrates core Python programming concepts through standalone scripts and unit tests. The project follows a modular structure where each week contains focused programming problems.

**Key Structure:**
- `week0/` - Foundational exercises (e.g., string manipulation, type conversion, physics calculations)
- Root-level scripts - Standalone utilities (e.g., `lower.py` for text processing)
- `week0/tests/` - Unit tests using pytest

## Code Patterns and Conventions

### Script Structure
All standalone scripts follow this standard pattern:
```python
def main():
    # Main logic here
    pass

if __name__ == "__main__":
    main()
```

**Why:** Allows scripts to be both executed directly and imported as modules without side effects.

### Function Conventions
- **Type hints are used:** Functions include input/output type annotations (see `week0/einstein.py` and `week0/tip.py`)
- **Input via `input()`:** User input is collected using the built-in `input()` function
- **String methods for parsing:** Currency/percentage conversion uses `.replace()` to strip symbols before casting (see `dollar_to_float()` and `percentage_to_float()` in `week0/tip.py`)

### Example Patterns
- **Math calculations:** `week0/einstein.py` demonstrates E=mc² with type hints and intermediate variable declarations
- **String operations:** `week0/playback.py` shows method chaining (e.g., `text.replace(" ", "...")`)
- **Type conversion:** `week0/tip.py` converts currency strings to floats by removing symbols

## Testing Approach

**Framework:** pytest is used for unit testing

**Test Location:** `week0/tests/` mirrors the structure of the main code directory

**Test Pattern** (from `test_einstein.py`):
```python
from python.week0.einstein import energy

def test_energy_one():
    assert energy(1) != 00000000000
```

**Note:** Tests are assertion-based and use absolute imports from the package root. Import paths follow the full package hierarchy (e.g., `from python.week0.einstein import energy`).

## Running Tests

Execute tests from the repository root:
```bash
pytest week0/tests/
```

## Common Development Tasks

- **Run a specific script:** `python week0/einstein.py`
- **Run all tests:** `pytest`
- **Run tests with verbose output:** `pytest -v`

## Key Files to Know

- `week0/einstein.py` - Reference example for type hints and physics calculations
- `week0/tip.py` - Reference example for helper functions and type conversion patterns
- `week0/tests/test_einstein.py` - Pytest import and assertion patterns
