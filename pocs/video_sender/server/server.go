package main

import(
    "net/http"
    "io/ioutil"
    "fmt"
)

func main(){
    http.HandleFunc("/",ImageHandler)
    http.ListenAndServe(":1337", nil)
}

func ImageHandler(rw http.ResponseWriter, req *http.Request){
    buf, _ := ioutil.ReadAll(req.Body)
    ioutil.WriteFile("image.jpg", buf, 0755)
    fmt.Println("Done writing")
}
