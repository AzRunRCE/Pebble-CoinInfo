Pebble.addEventListener('ready', function() {
  var data = {BTC:"0", ETH:"0",BCH:"0",LTC:"0"};
  console.log('Starting Javascript: ');
 
  httpRequest("https://api.kraken.com/0/public/Trades?pair=BTCEUR","GET",function(result) {
    data.BTC =Number(result.XXBTZEUR[result.XXBTZEUR.length - 1][0]).toFixed(2); 
    httpRequest("https://api.kraken.com/0/public/Trades?pair=ETHEUR","GET",function(result) {
      data.ETH = Number(result.XETHZEUR[result.XETHZEUR.length - 1][0]).toFixed(2);
      httpRequest("https://api.kraken.com/0/public/Trades?pair=BCHEUR","GET",function(result) {
        data.BCH = Number(result.BCHEUR[result.BCHEUR.length - 1][0]).toFixed(2);
        httpRequest("https://api.kraken.com/0/public/Trades?pair=LTCEUR","GET",function(result) {
          data.LTC = Number(result.XLTCZEUR[result.XLTCZEUR.length - 1][0]).toFixed(2);
        
        Pebble.sendAppMessage(data, function() {
          console.log('Message sent successfully: ' + JSON.stringify(data));
        }, function(e) {
          console.log('Message failed: ' + JSON.stringify(e));
        });
        
        
      });
    });
  });
});
});
    


function httpRequest(url,method,callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload =function () {
   callback(JSON.parse(this.responseText).result);
  };
  xhr.open(method, url);
  xhr.send();
}