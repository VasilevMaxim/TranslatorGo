

func main() {

	var (
		array [size]int = [size]int{4,1,2,6,0,123,4,23,1,0}
	)

	sortGrowth(array)
	//fmt.Println(sortGrowth(array))
	//fmt.Println(sortDecrease(array))
}


func sortGrowth(array [size]int) [size]int{
	for i := 0; i < size; i++{
		key := array[i]
		lo, hi := 0, i
		for lo < hi{
			mid := (hi + lo)/2
			if key < array[mid]{
				hi = mid
			} else {
				lo = mid + 1
			}
		}
		for j := i; j > lo; j--{
			array[j] = array[j-1]
		}
		array[lo] = key
	}
	return array
}

func sortDecrease(array [size]int) [size]int{
	for i := 0; i < size; i++{
		key := array[i]
		lo, hi := 0, i
		for lo < hi{
			mid := (hi + lo)/2
			if key > array[mid]{
				hi = mid
			} else {
				lo = mid + 1
			}
		}
		for j := i; j > lo; j--{
			array[j] = array[j-1]
		}
		array[lo] = key
	}
	return array
}
