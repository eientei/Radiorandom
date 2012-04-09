window.addEventListener("load",init,false);

var action_parent;
var install_action_a;
var total;

function init(e) {
    install_action_a = document.getElementById('install_action');

    install_action_a.addEventListener('click',perform_installer_action,false);
    install_action_a.href = '#perform_installer_action';
}

function calc_percent(parts, of) {
    return Math.round(100/of*parts);
}

function update_progress(current, total) {
    action_parent.innerHTML='Installing chunk ' + current + '/' + total + '  - ' + calc_percent(current,total) + '%'
    if (current == total) {
        action_parent.innerHTML += '<br/>';
        action_parent.innerHTML += 'Installation finished!';
        action_parent.innerHTML += '<br/>';
        action_parent.innerHTML += 'Now you can return to the <a href="/">index</a>';
    }
}

function perform_installer_action(e) {
    var parent = install_action_a.parentNode;
    parent.removeChild(install_action_a);
    action_parent = document.createElement('div');
    parent.appendChild(action_parent);

    var xhr = new XMLHttpRequest();

    xhr.open('get','/installer/install_finished/silent',true);
    xhr.send();

    var updater_xhr = new XMLHttpRequest();
    var last_call = 0;
    var delay = 100;
    var installing = true;
    updater_xhr.onreadystatechange = function() {
        if (updater_xhr.readyState === 4) {
            if (updater_xhr.status === 200) {
                var response = updater_xhr.responseText;
                var raw_result = JSON.parse(response);
                if (raw_result.error == null) {
                    var result = JSON.parse(raw_result.result);
                    installing = result.is_installing;
                    update_progress(result.current,result.total);
                } else {
                    alert(raw_result.error);
                }
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
                updater_xhr.open('post','/installer/rpc',false);
                updater_xhr.setRequestHeader("Content-Type","application/json");
                updater_xhr.send(request);
                recur();
            },waittime);
            last_call = new Date().getTime();
        }
    }
}

/*
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

function update_progress(current,total,state) {

}


*/
