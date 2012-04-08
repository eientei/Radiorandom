window.addEventListener("load",init,false);

var installing = false;

var action_parent;
var install_action_a;
var total;

function init(e) {
    install_action_a = document.getElementById('install_action');

    install_action_a.addEventListener('click',perform_installer_action,false);
    install_action_a.href = '#perform_installer_action';
}

function call_installation_process() {
    if (installing) {
        return;
    }

    installing = true;

    var xhr = new XMLHttpRequest();
    xhr.open('get','/installer/install_finished/silent',true);
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
            if (xhr.status === 200) {
                installing = false;
                action_parent.innerHTML='Installing chunk 0/0  - 0%';
                action_parent.innerHTML += '<br/>';
                action_parent.innerHTML += 'Installation finished!';
                action_parent.innerHTML += '<br/>';
                action_parent.innerHTML += 'Now you can return to the <a href="/">index</a>';
            }
        }
    }

    xhr.send();
    var parent = install_action_a.parentNode;
    parent.removeChild(install_action_a);
    action_parent = document.createElement('div');
    parent.appendChild(action_parent);
    action_parent.innerHTML='Installing chunk 0/0  - 0%';
}

function perform_installer_action(e) {
    call_installation_process();
    var xhr = new XMLHttpRequest();
    var last_call = 0;
    var delay = 100;
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
            if (xhr.status === 200) {
                var response = xhr.responseText;
                var raw_result = JSON.parse(response);
                if (raw_result.error == null) {
                    var result = JSON.parse(raw_result.result);
                    total = result.total;
                    if (installing) {
                        action_parent.innerHTML='Installing chunk ' + result.current + '/' + result.total + '  - 0%';
                    }
                } else {
                    alert(raw_result.error);
                }

                /*
                if (raw_result.erroor == null) {
                    var result = JSON.parse(raw_result.result);
                    alert(result.is_installing);
                } else {
                    alert(raw_result.error);
                }
                */
            }
        }
    }
    var request = '{"method":"install_progress","params":[],"id":1}';
    recur();

    function recur() {
        if (installing) {
            var curr_time =new Date().getTime();
            var diff = curr_time - last_call;
            var waittime=(diff<delay) ? (delay-diff) : 0;

            setTimeout(function() {
                xhr.open('post','/installer/rpc',false);
                xhr.setRequestHeader("Content-Type","application/json");
                xhr.send(request);
                recur();
            },waittime);
            last_call = new Date().getTime();
        }
    }

    /*


    */
    /*
    var xhr = new XMLHttpRequest();
    xhr.open('post','/installer/rpc')
    xhr.setRequestHeader("Content-Type","application/json");
    var request = '{"method":"sum","params":[1,2],"id":1}';
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
            var res;
            if (xhr.status === 200) {
                var response = xhr.responseText;
                alert(response);

            } else {
                res = 'invalid status';
            }
            alert(res);

        }
    }
    xhr.send(request);
    */
    return false;
}
