#include <pebble.h>

Window *my_window;
TextLayer *s_text_layer;
const uint32_t inbox_size = 128;
const uint32_t outbox_size = 0;
static char s_text[72];

enum {
  BTC,
  ETH,
  BCH
};

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
  Tuple *btcCurrencyTuple = dict_find(iter, BTC);
  Tuple *ethCurrencyTuple = dict_find(iter, ETH);
  Tuple *bchCurrencyTuple = dict_find(iter, BCH);
  static char s_btc[24];
  static char s_eth[24];
  static char s_bch[24];
  
  if(btcCurrencyTuple) {
    char *btcCurrency = btcCurrencyTuple->value->cstring;
    snprintf(s_btc, sizeof(s_btc), "BTC: %s€\n", btcCurrency);
  }
  strcpy(s_text,s_btc);
  
  if(ethCurrencyTuple) {
    char *ethCurrency  = ethCurrencyTuple->value->cstring;
    snprintf(s_eth, sizeof(s_eth), "ETH: %s€\n", ethCurrency);
  }
  strcat(s_text,s_eth);
  
  if(bchCurrencyTuple) {
    char *bchCurrency  = bchCurrencyTuple->value->cstring;
    snprintf(s_bch, sizeof(s_bch), "BCH: %s€", bchCurrency);
  }
  strcat(s_text,s_bch);
   APP_LOG(APP_LOG_LEVEL_ERROR, s_text,NULL);
  text_layer_set_text(s_text_layer, s_text);
  text_layer_set_text_alignment(s_text_layer,GTextAlignmentCenter);
}
static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped. Reason: %d", (int)reason);
}

void handle_init(void) {
  app_message_open(inbox_size, outbox_size);
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  my_window = window_create();
  window_stack_push(my_window, true);
  Layer *window_layer = window_get_root_layer(my_window);
  GRect bounds = layer_get_bounds(window_layer);
  GFont font = fonts_get_system_font(PBL_IF_RECT_ELSE(FONT_KEY_GOTHIC_28_BOLD, FONT_KEY_GOTHIC_28_BOLD));
  s_text_layer = text_layer_create(GRect(0, bounds.size.h /4, bounds.size.w, 85));
  text_layer_set_font(s_text_layer, font);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

void handle_deinit(void) {
  text_layer_destroy(s_text_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();  
}
