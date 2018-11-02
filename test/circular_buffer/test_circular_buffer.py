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
def test_push_back_element_past_capacity_overwrites_the_front_element():
    circular_buffer = CircularBuffer(3)

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_back(i)
        assert circular_buffer[i] == i

    assert circular_buffer.front() == 0
    circular_buffer.push_back(3)
    assert circular_buffer.front() == 1


@pytest.mark.circular_buffer
def test_push_front_element_past_capacity_overwrites_the_back_element():
    circular_buffer = CircularBuffer(3)

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_front(i)
        assert circular_buffer.front() == i

    assert circular_buffer.back() == 0
    circular_buffer.push_front(3)
    assert circular_buffer.front() == 3
    assert circular_buffer.back() == 1


@pytest.mark.circular_buffer
def test_push_front_increases_size_by_one():
    circular_buffer = CircularBuffer(10)
    assert circular_buffer.size() == 0

    circular_buffer.push_front(1)
    assert circular_buffer.size() == 1

    circular_buffer.push_front(2)
    assert circular_buffer.size() == 2


@pytest.mark.circular_buffer
def test_push_front_adds_element_to_the_front():
    circular_buffer = CircularBuffer(10)

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_front(i)
        assert circular_buffer.front() == i


@pytest.mark.circular_buffer
def test_pop_back_removes_the_element_at_the_back():
    circular_buffer = CircularBuffer(10)
    circular_buffer.push_back(1)
    circular_buffer.push_back(2)

    assert circular_buffer.back() == 2
    circular_buffer.pop_back()
    assert circular_buffer.back() == 1


@pytest.mark.circular_buffer
def test_pop_back_empty_buffer_raises_index_error():
    circular_buffer = CircularBuffer(10)
    with pytest.raises(IndexError):
        circular_buffer.pop_back()


@pytest.mark.circular_buffer
def test_pop_front_removes_first_element():
    circular_buffer = CircularBuffer(10)
    circular_buffer.push_front(1)
    circular_buffer.push_front(2)

    assert circular_buffer.front() == 2
    circular_buffer.pop_front()
    assert circular_buffer.front() == 1


@pytest.mark.circular_buffer
def test_pop_front_empty_buffer_raises_index_error():
    circular_buffer = CircularBuffer(10)
    with pytest.raises(IndexError):
        circular_buffer.pop_front()


@pytest.mark.circular_buffer
def test_front_return_first_element():
    circular_buffer = CircularBuffer(10)

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_front(i)
        assert circular_buffer.front() == i


@pytest.mark.circular_buffer
def test_front_on_empty_buffer_raises_index_error():
    circular_buffer = CircularBuffer(10)

    with pytest.raises(IndexError):
        circular_buffer.front()


@pytest.mark.circular_buffer
def test_back_return_last_element():
    circular_buffer = CircularBuffer(10)

    for i in range(circular_buffer.capacity()):
        circular_buffer.push_back(i)
        assert circular_buffer.back() == i


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


@pytest.mark.circular_buffer
def test_iterate_returns_each_element():
    circular_buffer = CircularBuffer(10)
    index = 0

    for buffer in circular_buffer:
        assert buffer == circular_buffer.at(index)
        index += 1
