import pytest
from pyboost.multiprecision import CheckedUInt128, CheckedUInt256, CheckedUInt512, CheckedUInt1024, CheckedInt128, \
    CheckedInt256, CheckedInt512, CheckedInt1024

ALL_CHECKED_INTEGER_TYPES = [CheckedUInt128, CheckedUInt256, CheckedUInt512, CheckedUInt1024, CheckedInt128,
                             CheckedInt256, CheckedInt512, CheckedInt1024]

ALL_CHECKED_SIGNED_INTEGER_TYPES = [CheckedInt128, CheckedInt256, CheckedInt512, CheckedInt1024]
ALL_CHECKED_UNSIGNED_INTEGER_TYPES = [CheckedUInt128, CheckedUInt256, CheckedUInt512, CheckedUInt1024]


@pytest.mark.multiprecision
@pytest.mark.parametrize("CppIntClass", ALL_CHECKED_INTEGER_TYPES)
def test_checked_integers_default_initialized_to_zero(CppIntClass):
    cpp_int = CppIntClass()

    assert cpp_int.is_zero()


@pytest.mark.multiprecision
@pytest.mark.parametrize("CppIntClass", ALL_CHECKED_SIGNED_INTEGER_TYPES)
def test_checked_signed_underflow_raises_overflow_error(CppIntClass):
    i = CppIntClass()
    i -= CppIntClass(str(2 ** CppIntClass.num_bits() - 1))

    with pytest.raises(OverflowError):
        i -= CppIntClass(str(2 ** CppIntClass.num_bits() - 1))


@pytest.mark.multiprecision
@pytest.mark.parametrize("CppIntClass", ALL_CHECKED_SIGNED_INTEGER_TYPES)
def test_checked_signed_overflow_raises_overflow_error(CppIntClass):
    i = CppIntClass()
    i += CppIntClass(str(2 ** CppIntClass.num_bits() - 1))

    with pytest.raises(OverflowError):
        i += CppIntClass(str(2 ** CppIntClass.num_bits() - 1))


@pytest.mark.multiprecision
@pytest.mark.parametrize("CppIntClass", ALL_CHECKED_INTEGER_TYPES)
def test_checked_signed_integer_constructor_throws_when_string_value_cannot_be_represented_by_integer(CppIntClass):
    with pytest.raises(ValueError):
        CppIntClass(str(2 ** CppIntClass.num_bits() + 1))


@pytest.mark.multiprecision
@pytest.mark.parametrize("CppIntClass", ALL_CHECKED_SIGNED_INTEGER_TYPES)
def test_checked_signed_integer_constructor_accepts_string_values_with_same_precision_as_integer(CppIntClass):
    CppIntClass(str(2 ** CppIntClass.num_bits() - 1))


@pytest.mark.multiprecision
@pytest.mark.parametrize("CppIntClass", ALL_CHECKED_UNSIGNED_INTEGER_TYPES)
def test_checked_unsigned_integer_constructor_accepts_string_values_with_same_precision_as_integer(CppIntClass):
    CppIntClass(str(2 ** CppIntClass.num_bits() - 1))
