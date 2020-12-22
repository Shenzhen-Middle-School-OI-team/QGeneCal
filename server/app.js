var express = require('express')
var bodyParser = require('body-parser');
var fs = require('fs')
var child_process = require("child_process");
const { exec } = require('child_process');
var app = express()
var count = 0;
app.use(bodyParser.urlencoded({
    extended: true
}))

app.post('/calc/:id/', async (req, res) => {
    count = count + 1
    //console.log(req.body.s);
    var data_name = child_process.execSync("cat /dev/urandom | head -n 10 | md5sum | head -c 10").toString();
    fs.writeFileSync("./program/" + data_name + ".in", req.body.s, err => { err ? console.log('写入失败') : console.log('写入成功'); })
    var name;
    if (req.params.id == 1) {
        name = "trival_model";
    }
    else if (req.params.id == 2) {
        name = "incomplete_dominance";
    }
    else {
        res.send({ success: false, ret: "你在想桃子？" });
    }
    exec("cd program && ./" + name + " < " + data_name + ".in", { timeout: 2000 }, (error, stdout, stderr,) => {
        if (stderr) {
            //console.error(`执行的错误: ${stderr}`);
            res.send({ success: false, ret: stderr });
        }
        else {
            //console.log(`成功: ${stdout}`);
            res.send({ success: true, ret: stdout });
        }
    });
    console.log("一共收到 " + count + " 次请求");
    child_process.execSync("rm ./program/" + data_name + ".in");
})

app.post('/recompile', async (req, res) => {
    exec("cd program && g++ incomplete_dominance.cpp -o incomplete_dominance && g++ trival_model.cpp -o trival_model", { timeout: 10000 }, (error, stdout, stderr,) => {
        if (error) {
            //console.log(`执行的错误: ${error}`);
            res.send({ success: false, ret: stderr });
        }
        else {
            //console.log(`成功: ${stdout}`);
            res.send({ success: true, ret: stdout });
        }
    });
})

app.get('/', function (req, res) {
    res.sendFile(__dirname + "/" + "index.html");
})

app.get('/program/:name/', function (req, res) {
    res.sendFile(__dirname + "/program/" + req.params.name + ".cpp");
})

var server = app.listen(3000)

console.log('Server running at http://127.0.0.1:3000/');
