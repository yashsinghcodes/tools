package main

import (
    "fmt"
    "os"
    "github.com/emirpasic/gods/sets/hashset"
)


func main() { 
    input, _ := os.ReadFile("input");
    for i := 0; i < len(input)-4; i++ {
        set := hashset.New()
        for _, v := range input[i:i+4]{
            set.Add(v)
        }
        if len(set.Values()) == 4 {
            fmt.Println(i+4)
            break
        }
    }
}
