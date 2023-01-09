var go = "../../html_images/go_sign.png";
var st = "../../html_images/stop_b.png";

var i = 0;

function validation() {
    i = i +1;
 //   if (i == 0)
 //       postMessage();
 //   else if (i == 1)
        postMessage(i);
  setTimeout("timedCount()", 500);
}

timedCount();
