
const size int= 2
func main() {

	var (
		array1 [size]int = [size]int{4,1,2,6,0,123,4,23,1,0}
	)
	array1[5] = 2
	sortGrowth(array1)
	//fmt.Println(sortGrowth(array))
	//fmt.Println(sortDecrease(array))
}


func sortGrowth(array2 [size]int) [size]int{
	for i := 0; i < size; i++{
		key := array2[i]
		lo := 0
		hi := i
		for lo < hi{
			mid := (hi + lo)/2
			if key < array2[mid]{
				hi = mid
			} else {
				lo = mid + 1
			}
		}
		for j := i; j > lo; j--{
			array2[j] = array2[j-1]
		}
		array2[lo] = key
	}
	return array2
}

func sortDecrease(array3 [size]int) [size]int{
	for i := 0; i < size; i++{
		key := array3[i]
		lo := 0
		hi := i
		for lo < hi{
			mid := (hi + lo)/2
			if key > array3[mid]{
				hi = mid
			} else {
				lo = mid + 1
			}
		}
		for j := i; j > lo; j--{
			array3[j] = array3[j-1]
		}
		array3[lo] = key
	}
	return array
}
