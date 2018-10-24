import pytest

from pyboost.dynamic_bitset import DynamicBitset, DynamicBitset8, DynamicBitset16, DynamicBitset32, DynamicBitset64

ALL_DYNAMIC_BITSET_CLASSES = [DynamicBitset, DynamicBitset8, DynamicBitset16, DynamicBitset32, DynamicBitset64]


@pytest.mark.dynamic_bitset
@pytest.mark.parametrize("BitsetClass", ALL_DYNAMIC_BITSET_CLASSES)
def test_dynamic_bitset_is_all_zeroes_when_first_initialized_with_just_size_parameter(BitsetClass):
    bitset = BitsetClass(100)

    assert all(bit == 0 for bit in bitset)


@pytest.mark.dynamic_bitset
@pytest.mark.parametrize("BitsetClass", ALL_DYNAMIC_BITSET_CLASSES)
def test_dynamic_bitset_is_all_zeroes_when_first_initialized_with_size_and_value(BitsetClass):
    bitset = BitsetClass(100, 0)

    assert all(bit == 0 for bit in bitset)


@pytest.mark.dynamic_bitset
@pytest.mark.parametrize("BitsetClass", ALL_DYNAMIC_BITSET_CLASSES)
def test_dynamic_bitset_initialized_with_the_bits_from_the_given_value(BitsetClass):
    bitset = BitsetClass(8, 255)

    assert all(bit == 1 for bit in bitset)


@pytest.mark.dynamic_bitset
@pytest.mark.parametrize("BitsetClass", ALL_DYNAMIC_BITSET_CLASSES)
def test_dynamic_bitset_is_initialized_with_the_correct_sized(BitsetClass):
    bitset = BitsetClass(64)

    assert bitset.size() == 64


@pytest.mark.dynamic_bitset
@pytest.mark.parametrize("BitsetClass", ALL_DYNAMIC_BITSET_CLASSES)
def test_dynamic_bitset_is_initialized_with_the_correct_len(BitsetClass):
    bitset = BitsetClass(128)

    assert len(bitset) == 128
    assert len(bitset) == bitset.size()
