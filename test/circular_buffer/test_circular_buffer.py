import pytest

from pyboost.circular_buffer import CircularBuffer


@pytest.mark.circular_buffer
def test_clear_removes_all_elements():
    circular_buffer = CircularBuffer(10)

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_back(i)

    assert not circular_buffer.empty()
    circular_buffer.clear()
    assert circular_buffer.empty()


@pytest.mark.circular_buffer
def test_push_back_increases_size_by_one():
    circular_buffer = CircularBuffer(10)
    assert circular_buffer.size() == 0

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_back(i)
        assert circular_buffer.size() == i + 1


@pytest.mark.circular_buffer
@pytest.mark.parametrize("elements", [(1, 2, 3)])
def test_push_back_element_past_capacity_overwrites_the_front_element(elements):
    circular_buffer = CircularBuffer(3)
    for element in elements:
        circular_buffer.push_back(element)

    assert circular_buffer.front() == 1
    circular_buffer.push_back(4)
    assert circular_buffer.front() == 2


@pytest.mark.circular_buffer
@pytest.mark.parametrize("elements", [(1, 2, 3)])
def test_push_front_element_past_capacity_overwrites_the_back_element(elements):
    circular_buffer = CircularBuffer(3)
    for element in elements:
        circular_buffer.push_back(element)

    assert circular_buffer.back() == 3
    circular_buffer.push_front(4)
    assert circular_buffer.back() == 2


@pytest.mark.circular_buffer
def test_push_front_increases_size_by_one():
    circular_buffer = CircularBuffer(10)
    assert circular_buffer.size() == 0

    circular_buffer.push_front(1)
    assert circular_buffer.size() == 1

    circular_buffer.push_front(2)
    assert circular_buffer.size() == 2


@pytest.mark.circular_buffer
@pytest.mark.parametrize("elements", [(1, 2, 3, 4)])
def test_push_front_adds_element_to_the_front(elements):
    circular_buffer = CircularBuffer(10)

    for element in elements:
        circular_buffer.push_front(element)
        assert circular_buffer.front() == element


@pytest.mark.circular_buffer
def test_pop_back_removes_the_element_at_the_back():
    circular_buffer1 = CircularBuffer(10)
    circular_buffer1.push_back(1)
    circular_buffer1.push_back(2)

    assert circular_buffer1.back() == 2
    circular_buffer1.pop_back()
    assert circular_buffer1.back() == 1


@pytest.mark.circular_buffer
def test_pop_back_empty_buffer_raises_index_error():
    circular_buffer = CircularBuffer(10)
    with pytest.raises(IndexError):
        circular_buffer.pop_back()


@pytest.mark.circular_buffer
def test_pop_front_removes_first_element():
    circular_buffer1 = CircularBuffer(10)
    circular_buffer1.push_front(1)
    circular_buffer1.push_front(2)

    assert circular_buffer1.front() == 2
    circular_buffer1.pop_front()
    assert circular_buffer1.front() == 1


@pytest.mark.circular_buffer
def test_pop_front_empty_buffer_raises_index_error():
    circular_buffer = CircularBuffer(10)
    with pytest.raises(IndexError):
        circular_buffer.pop_front()


@pytest.mark.circular_buffer
@pytest.mark.parametrize("elements", [(1, 2, 3)])
def test_front_return_first_element(elements):
    circular_buffer = CircularBuffer(10)

    for element in elements:
        circular_buffer.push_back(element)

    assert circular_buffer.front() == 1


@pytest.mark.circular_buffer
def test_front_on_empty_buffer_raises_index_error():
    circular_buffer = CircularBuffer(10)

    with pytest.raises(IndexError):
        circular_buffer.front()


@pytest.mark.circular_buffer
@pytest.mark.parametrize("elements", [(1, 2, 3)])
def test_back_return_last_element(elements):
    circular_buffer = CircularBuffer(10)

    for element in elements:
        circular_buffer.push_back(element)

    assert circular_buffer.back() == 3


@pytest.mark.circular_buffer
def test_back_on_empty_buffer_raises_index_error():
    circular_buffer = CircularBuffer(10)

    with pytest.raises(IndexError):
        circular_buffer.back()


@pytest.mark.circular_buffer
def test_full_return_true_after_filling_the_buffer_to_capacity():
    circular_buffer = CircularBuffer(3)

    for i in range(circular_buffer.capacity()):
        assert not circular_buffer.full()
        circular_buffer.push_back(i)

    assert circular_buffer.full()


@pytest.mark.circular_buffer
def test_empty_return_true_after_clearing_the_buffer():
    circular_buffer = CircularBuffer(3)

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_back(i)

    for i in range(circular_buffer.capacity()):
        assert not circular_buffer.empty()
        circular_buffer.pop_back()

    assert circular_buffer.empty()


@pytest.mark.circular_buffer
def test_size_equals_capacity_after_filling_the_buffer_to_capacity():
    circular_buffer = CircularBuffer(10)

    for i in range(circular_buffer.capacity()):
        assert circular_buffer.size() != circular_buffer.capacity()
        circular_buffer.push_back(i)

    assert circular_buffer.size() == circular_buffer.capacity()


@pytest.mark.circular_buffer
def test_at_index_returns_element_at_index():
    circular_buffer = CircularBuffer(10)

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_back(i)

    for i in range(circular_buffer.capacity()):
        assert circular_buffer.at(i) == i


@pytest.mark.circular_buffer
def test_accessing_empty_buffer_raises_index_error():
    circular_buffer = CircularBuffer(10)

    with pytest.raises(IndexError):
        circular_buffer.at(0)


@pytest.mark.circular_buffer
@pytest.mark.parametrize("capacity", [10, 100, 1000, 10000])
def test_capacity_returns_capacity_specified_in_constructor(capacity):
    circular_buffer = CircularBuffer(capacity)

    assert circular_buffer.capacity() == capacity
