Pebble.addEventListener('ready', function() {
  var data = {BTC:"0", ETH:"0",BCH:"0"};
  console.log('Starting Javascript: ');
 
  httpRequest("https://api.kraken.com/0/public/Trades?pair=BTCEUR","GET",function(text) {
    var objBTC = JSON.parse(text);
    data.BTC =Number(objBTC.result.XXBTZEUR[0][0]).toFixed(2);
    httpRequest("https://api.kraken.com/0/public/Trades?pair=ETHEUR","GET",function(text) {
      var objETH = JSON.parse(text);
      data.ETH = Number(objETH.result.XETHZEUR[0][0]).toFixed(2);
      httpRequest("https://api.kraken.com/0/public/Trades?pair=BCHEUR","GET",function(text) {
        var objBCH = JSON.parse(text);
        data.BCH = Number(objBCH.result.BCHEUR[0][0]).toFixed(2);
        Pebble.sendAppMessage(data, function() {
          console.log('Message sent successfully: ' + JSON.stringify(data));
        }, function(e) {
          console.log('Message failed: ' + JSON.stringify(e));
        });
      });
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