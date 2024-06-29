std::string client = R"(<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Websocket Client ...</title>
<script>
  window.addEventListener("load", function(evt) {
    var output = document.getElementById("output");
    var input = document.getElementById("input");
    var ws;
    var print = function(...args) {
      var d = document.createElement("div");
      for (let i = 0; i < args.length; i += 2) {
        var color = args[i];
        var text = args[i + 1];
        var span = document.createElement("span");
          span.textContent = text;
          span.style.color = color;
          d.appendChild(span);
      }
      output.appendChild(d);
      output.scroll(0, output.scrollHeight);
    };
    document.getElementById("open").onclick = function(evt) {
      if (ws) return false;
      const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    	const host = window.location.host;
    	const wsurl = `${protocol}//${host}/reverse`;
      ws = new WebSocket(wsurl);
      ws.onopen = function(evt) {
        print("BLACK","OPEN: ","RED",wsurl);
      }
      ws.onclose = function(evt) {
        print("RED","CLOSE");
        ws = null;
      }
      ws.onmessage = function(evt) {
        print("BLACK","R: ","GREEN", evt.data);
      }
      ws.onerror = function(evt) {
        print("RED","ERROR: ","BLACK",evt.data);
      }
      return false;
    };
    document.getElementById("send").onclick = function(evt) {
      if (!ws) {
        print("RED","ERROR: ","BLUE", "please ","GREEN","OPEN","BLUE"," connection first");
        return false;
      }
      print("BLACK","S: ", "BLUE", input.value);
      ws.send(input.value);
      return false;
    };
    document.getElementById("close").onclick = function(evt) {
      if (!ws) return false;
      ws.close();
      return false;
    };
    document.getElementById("clear").onclick = function(evt) {
      while(output.firstChild) {
        output.removeChild(output.firstChild);
      }
      console.log('clear ...');
      return false;
    };
  });
</script>
</head>
<body>
<table>
  <tr>
    <td valign="top" width="50%">
      <p>Click "Open" to create a connection to the server, "Send" to send a message to the server and "Close" to close the connection.
      You can change the message and send multiple times.<p>
      <form>
        <button id="open">Open</button>
        <button id="close">Close</button>
        <button id="clear">Clear</button>
        <p><input id="input" type="text" value="Hello world!">
        <button id="send">Send</button>
      </form>
    </td>
  </tr>
  <tr>
    <td valign="top" width="100%">
      <div id="output" style="max-height: 70vh;overflow-y: scroll;"></div>
    </td>
  </tr>
</table>
</body>
</html>)";
