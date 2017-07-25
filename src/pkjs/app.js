Pebble.addEventListener('ready', function() {
  var data = {BTC:"0", ETH:"0"};
  console.log('PebbleKit JS ready!');
  httpRequest("https://api.cryptonator.com/api/ticker/btc-eur","GET",function(text) {
    var obj = JSON.parse(text);
    data.BTC =Number(obj.ticker.price).toFixed(2);
  });
  httpRequest("https://api.cryptonator.com/api/ticker/eth-eur","GET",function(text) {
    var obj = JSON.parse(text);
    data.ETH =Number(obj.ticker.price).toFixed(2);
    Pebble.sendAppMessage(data, function() {
      console.log('Message sent successfully: ' + JSON.stringify(data));
      }, function(e) {
      console.log('Message failed: ' + JSON.stringify(e));
      });
  });

});

function httpRequest(url,method,callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload =function () {
   callback(this.responseText);
  };
  xhr.open(method, url);
  xhr.send();
}