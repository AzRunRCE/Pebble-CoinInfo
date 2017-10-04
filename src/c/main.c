#include <pebble.h>

Window *my_window;
TextLayer *s_text_layer;
const uint32_t inbox_size = 128;
const uint32_t outbox_size = 0;
static char s_text[94];

enum {
  BTC,
  ETH,
  BCH,
  LTC
};

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
  Tuple *btcCurrencyTuple = dict_find(iter, BTC);
  Tuple *ethCurrencyTuple = dict_find(iter, ETH);
  Tuple *bchCurrencyTuple = dict_find(iter, BCH);
  Tuple *ltcCurrencyTuple = dict_find(iter, LTC);
  
  static char s_tmp[24];

  
  if(btcCurrencyTuple) {
    snprintf(s_tmp, sizeof(s_tmp), "BTC: %s€\n", btcCurrencyTuple->value->cstring);
    strcpy(s_text,s_tmp);
  }
  if(ethCurrencyTuple) {
    snprintf(s_tmp, sizeof(s_tmp), "ETH: %s€\n",  ethCurrencyTuple->value->cstring);
    strcat(s_text,s_tmp);
  }
  if(bchCurrencyTuple) {
    snprintf(s_tmp, sizeof(s_tmp), "BCH: %s€\n", bchCurrencyTuple->value->cstring);
    strcat(s_text,s_tmp);
  }
  if(bchCurrencyTuple) {
    snprintf(s_tmp, sizeof(s_tmp), "LTC: %s€", ltcCurrencyTuple->value->cstring);
    strcat(s_text,s_tmp);
  }
 
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
  s_text_layer = text_layer_create(GRect(0, 20, bounds.size.w,  120));
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
