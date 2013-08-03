/*jslint evil:true */
/**
 * Dynamic thread loader
 *
 * 
 * 
 * 
 * 
 * 
*/

// 
var DISQUS;
if (!DISQUS || typeof DISQUS == 'function') {
    throw "DISQUS object is not initialized";
}
// 

// json_data and default_json django template variables will close
// and re-open javascript comment tags

(function () {
    var jsonData, cookieMessages, session, key;

    /* */ jsonData = {"reactions": [], "reactions_limit": 10, "ordered_highlighted": [], "posts": {"382214984": {"edited": false, "author_is_moderator": false, "from_request_user": null, "up_voted": false, "can_edit": false, "ip": "", "last_modified_date": null, "dislikes": 0, "raw_message": "Could i change the 74HCT164 for a 74HC595 would the wiring be the same or different??", "has_replies": false, "vote": false, "votable": true, "last_modified_by": null, "real_date": "2011-07-21_07:19:06", "date": "5 months ago", "message": "Could i change the 74HCT164 for a 74HC595 would the wiring be the same or different??", "approved": true, "is_last_child": false, "author_is_founder": false, "can_reply": true, "likes": 0, "user_voted": null, "num_replies": 0, "down_voted": false, "is_first_child": false, "has_been_anonymized": false, "highlighted": false, "parent_post_id": null, "depth": 0, "points": 0, "user_key": "fd7723e77643d96f3018c2efd7a2a87d", "author_is_creator": false, "email": "", "killed": false, "is_realtime": false}, "382214986": {"edited": false, "author_is_moderator": false, "from_request_user": null, "up_voted": false, "can_edit": false, "ip": "", "last_modified_date": null, "dislikes": 0, "raw_message": "any special instructions for startup of the lcd? at first everything worked fine but now it seems like the lcd controller and not loading ok and it goes into 1 line mode. also some characters are not what they should be.", "has_replies": false, "vote": false, "votable": true, "last_modified_by": null, "real_date": "2011-05-26_17:21:01", "date": "7 months ago", "message": "any special instructions for startup of the lcd? at first everything worked fine but now it seems like the lcd controller and not loading ok and it goes into 1 line mode. also some characters are not what they should be.", "approved": true, "is_last_child": false, "author_is_founder": false, "can_reply": true, "likes": 0, "user_voted": null, "num_replies": 0, "down_voted": false, "is_first_child": false, "has_been_anonymized": false, "highlighted": false, "parent_post_id": null, "depth": 0, "points": 0, "user_key": "1d116f6eff0e6ad4f7ce33b617a142aa", "author_is_creator": false, "email": "", "killed": false, "is_realtime": false}, "382214988": {"edited": false, "author_is_moderator": false, "from_request_user": null, "up_voted": false, "can_edit": false, "ip": "", "last_modified_date": null, "dislikes": 0, "raw_message": "Hi,\n\nI've tried the above codes and circuit and it doesn't seem to be working although I did exactly the same as you mentioned.\n\nDo you know what might be the problem I'm facing? Could you please reply me if you think my problem is?\n\ni'm using ATMEGA88PA-PU\n\nwhat clock frequency do i need to use it for this? thanks", "has_replies": false, "vote": false, "votable": true, "last_modified_by": null, "real_date": "2010-05-15_06:40:36", "date": "1 year ago", "message": "Hi,<br><br>I've tried the above codes and circuit and it doesn't seem to be working although I did exactly the same as you mentioned.<br><br>Do you know what might be the problem I'm facing? Could you please reply me if you think my problem is?<br><br>i'm using ATMEGA88PA-PU<br><br>what clock frequency do i need to use it for this? thanks", "approved": true, "is_last_child": false, "author_is_founder": false, "can_reply": true, "likes": 0, "user_voted": null, "num_replies": 0, "down_voted": false, "is_first_child": false, "has_been_anonymized": false, "highlighted": false, "parent_post_id": null, "depth": 0, "points": 0, "user_key": "df853a1174f9aaadd22f4b83193a1437", "author_is_creator": false, "email": "", "killed": false, "is_realtime": false}, "382214989": {"edited": false, "author_is_moderator": false, "from_request_user": null, "up_voted": false, "can_edit": false, "ip": "", "last_modified_date": null, "dislikes": 0, "raw_message": "/* \n *  Prints a string at line 1 of the LCD\n *\n*/\nvoid lcd_puts_1(const unsigned char *str) {\n\tuint8_t i;\n\n        /* goto line 1 */\n        lcd_move_cursor(LCD_LINE_1, 0);\n        \n\ti=0;\n\twhile (str[i] &#38;&#38; (i", "has_replies": false, "vote": false, "votable": true, "last_modified_by": null, "real_date": "2009-04-12_22:51:34", "date": "2 years ago", "message": "/* <br> *  Prints a string at line 1 of the LCD<br> *<br>*/<br>void lcd_puts_1(const unsigned char *str) {<br>\tuint8_t i;<br><br>        /* goto line 1 */<br>        lcd_move_cursor(LCD_LINE_1, 0);<br>        <br>\ti=0;<br>\twhile (str[i] &amp;&amp; (i", "approved": true, "is_last_child": false, "author_is_founder": false, "can_reply": true, "likes": 0, "user_voted": null, "num_replies": 0, "down_voted": false, "is_first_child": false, "has_been_anonymized": false, "highlighted": false, "parent_post_id": null, "depth": 0, "points": 0, "user_key": "c02a791f30d9aa8f48e3c85404a2be45", "author_is_creator": false, "email": "", "killed": false, "is_realtime": false}, "382214991": {"edited": false, "author_is_moderator": false, "from_request_user": null, "up_voted": false, "can_edit": false, "ip": "", "last_modified_date": null, "dislikes": 0, "raw_message": "Hello, I just now come across this blog whilst I'm browsing around online as I am seeking some material on LCD TVs!. I think it's a very interesting site so I have bookmarked your site and will revisit another day to give it a better read when I have more time.", "has_replies": false, "vote": false, "votable": true, "last_modified_by": null, "real_date": "2009-11-30_09:33:53", "date": "2 years ago", "message": "Hello, I just now come across this blog whilst I'm browsing around online as I am seeking some material on LCD TVs!. I think it's a very interesting site so I have bookmarked your site and will revisit another day to give it a better read when I have more time.", "approved": true, "is_last_child": false, "author_is_founder": false, "can_reply": true, "likes": 0, "user_voted": null, "num_replies": 0, "down_voted": false, "is_first_child": false, "has_been_anonymized": false, "highlighted": false, "parent_post_id": null, "depth": 0, "points": 0, "user_key": "0305539f1f4670fd613a23aa915b2c4a", "author_is_creator": false, "email": "", "killed": false, "is_realtime": false}}, "ordered_posts": [382214984, 382214986, 382214988, 382214991, 382214989], "realtime_enabled": false, "ready": true, "mediaembed": [], "has_more_reactions": false, "realtime_paused": true, "integration": {"receiver_url": "", "hide_user_votes": false, "reply_position": true, "disqus_logo": false}, "highlighted": {}, "reactions_start": 0, "media_url": "http://mediacdn.disqus.com/1325732276", "users": {"0305539f1f4670fd613a23aa915b2c4a": {"username": "Amie Dejarnette", "tumblr": "", "about": "", "display_name": "Amie Dejarnette", "url": "http://disqus.com/guest/0305539f1f4670fd613a23aa915b2c4a/", "registered": false, "remote_id": null, "linkedin": "", "blog": "http://www.42inchlcdtv.org", "remote_domain": "", "points": null, "facebook": "", "avatar": "http://mediacdn.disqus.com/1325732276/images/noavatar32.png", "delicious": "", "is_remote": false, "verified": false, "flickr": "", "twitter": "", "remote_domain_name": ""}, "df853a1174f9aaadd22f4b83193a1437": {"username": "Jamie", "tumblr": "", "about": "", "display_name": "Jamie", "url": "http://disqus.com/guest/df853a1174f9aaadd22f4b83193a1437/", "registered": false, "remote_id": null, "linkedin": "", "blog": "", "remote_domain": "", "points": null, "facebook": "", "avatar": "http://mediacdn.disqus.com/1325732276/images/noavatar32.png", "delicious": "", "is_remote": false, "verified": false, "flickr": "", "twitter": "", "remote_domain_name": ""}, "fd7723e77643d96f3018c2efd7a2a87d": {"username": "jsmxbox", "tumblr": "", "about": "", "display_name": "jsmxbox", "url": "http://disqus.com/guest/fd7723e77643d96f3018c2efd7a2a87d/", "registered": false, "remote_id": null, "linkedin": "", "blog": "", "remote_domain": "", "points": null, "facebook": "", "avatar": "http://mediacdn.disqus.com/1325732276/images/noavatar32.png", "delicious": "", "is_remote": false, "verified": false, "flickr": "", "twitter": "", "remote_domain_name": ""}, "1d116f6eff0e6ad4f7ce33b617a142aa": {"username": "tom", "tumblr": "", "about": "", "display_name": "tom", "url": "http://disqus.com/guest/1d116f6eff0e6ad4f7ce33b617a142aa/", "registered": false, "remote_id": null, "linkedin": "", "blog": "", "remote_domain": "", "points": null, "facebook": "", "avatar": "http://mediacdn.disqus.com/1325732276/images/noavatar32.png", "delicious": "", "is_remote": false, "verified": false, "flickr": "", "twitter": "", "remote_domain_name": ""}, "c02a791f30d9aa8f48e3c85404a2be45": {"username": "Valera", "tumblr": "", "about": "", "display_name": "Valera", "url": "http://disqus.com/guest/c02a791f30d9aa8f48e3c85404a2be45/", "registered": false, "remote_id": null, "linkedin": "", "blog": "", "remote_domain": "", "points": null, "facebook": "", "avatar": "http://mediacdn.disqus.com/1325732276/images/noavatar32.png", "delicious": "", "is_remote": false, "verified": false, "flickr": "", "twitter": "", "remote_domain_name": ""}}, "user_unapproved": {}, "messagesx": {"count": 0, "unread": []}, "thread": {"voters_count": 0, "offset_posts": 0, "slug": "avr_3_wire_hd44780_lcd_interface_avr_gcc", "paginate": true, "num_pages": 2, "days_alive": 0, "moderate_none": false, "voters": {}, "total_posts": 9, "realtime_paused": true, "queued": false, "pagination_type": "append", "user_vote": null, "likes": 0, "num_posts": 5, "closed": false, "per_page": 5, "id": 497834386, "killed": false, "moderate_all": false}, "forum": {"use_media": false, "avatar_size": 32, "apiKey": "aI4NZEaE3iZuCuZICTr144qjaSFXmlfyXZw6qg0XkUUI6Ssg1wUyiFl6Wj2XKIdS", "features": {}, "use_old_templates": false, "comment_max_words": 0, "mobile_theme_disabled": false, "linkbacks_enabled": false, "is_early_adopter": false, "allow_anon_votes": true, "revert_new_login_flow": false, "stylesUrl": "http://mediacdn.disqus.com/uploads/styles/105/6646/micahcarrick.css", "login_buttons_enabled": true, "streaming_realtime": false, "show_avatar": true, "reactions_enabled": true, "reply_position": true, "id": 1056646, "name": "Micah Carrick", "language": "en", "mentions_enabled": false, "url": "micahcarrick", "allow_anon_post": true, "disqus_auth_disabled": false, "thread_votes_disabled": true, "default_avatar_url": "http://mediacdn.disqus.com/1325732276/images/noavatar32.png", "ranks_enabled": false, "template": {"url": "http://mediacdn.disqus.com/1325732276/build/themes/dsq7884a9652e94555c70f96b6be63be216.js?82", "mobile": {"url": "http://mediacdn.disqus.com/1325732276/build/themes/newmobile.js", "css": "http://mediacdn.disqus.com/1325732276/build/themes/newmobile.css"}, "api": "1.1", "name": "Houdini", "css": "http://mediacdn.disqus.com/1325732276/build/themes/dsq7884a9652e94555c70f96b6be63be216.css?82"}, "hasCustomStyles": false, "max_depth": 0, "lastUpdate": 1323365546, "moderate_all": false}, "settings": {"realtimeHost": "qq.disqus.com", "uploads_url": "http://media.disqus.com/uploads", "ssl_media_url": "https://securecdn.disqus.com/1325732276", "realtime_url": "http://rt.disqus.com/forums/realtime-cached.js", "facebook_app_id": "52254943976", "minify_js": true, "recaptcha_public_key": "6LdKMrwSAAAAAPPLVhQE9LPRW4LUSZb810_iaa8u", "read_only": false, "facebook_api_key": "52254943976", "realtimePort": "80", "debug": false, "disqus_url": "http://disqus.com", "media_url": "http://mediacdn.disqus.com/1325732276"}, "ranks": {}, "request": {"sort": "newest", "is_authenticated": false, "user_type": "anon", "subscribe_on_post": 0, "missing_perm": null, "user_id": null, "remote_domain_name": "", "remote_domain": "", "is_verified": false, "profile_url": "", "username": "", "is_global_moderator": false, "sharing": {}, "timestamp": "2012-01-07_00:14:36", "is_moderator": false, "ordered_unapproved_posts": [], "unapproved_posts": {}, "forum": "micahcarrick", "is_initial_load": true, "display_username": "", "points": null, "has_email": false, "moderator_can_edit": false, "is_remote": false, "userkey": "", "page": 1}, "context": {"use_twitter_signin": true, "use_fb_connect": true, "show_reply": true, "active_switches": ["autocommitted_thread", "bespin", "community_icon", "embedapi", "google_auth", "mentions", "new_facebook_auth", "new_thread_create", "realtime_cached", "show_captcha_on_links", "ssl", "static_reply_frame", "static_styles", "statsd_created", "upload_media", "use_rs_paginator_60m"], "sigma_chance": 10, "use_google_signin": true, "switches": {"olark_admin_addons": true, "listactivity_replies": true, "es_index_threads": true, "use_master_for_api": true, "google_auth": true, "html_email": true, "statsd.timings": true, "community_icon": true, "show_captcha_on_links": true, "olark_admin_packages": true, "static_styles": true, "stats": true, "realtime": true, "realtime_cached": true, "statsd_created": true, "bespin": true, "olark_support": true, "firehose_gnip": true, "olark_addons": true, "new_facebook_auth": true, "limit_get_posts_days_30d": true, "edits_to_spam": true, "phoenix": true, "new_thread_create": true, "use_impermium": true, "upload_media": false, "vip_read_slave": true, "embedapi": true, "ssl": true, "autocommitted_thread": true, "send_to_impermium": true, "theme_editor_disabled": true, "train_impermium": true, "listactivity_replies_30d": true, "firehose_gnip_http": true, "moderate_ascending": true, "git_themes": true, "new_moderate": true, "use_rs_paginator_60m": true, "redis_threadcount": true, "mentions": true, "olark_install": true, "static_reply_frame": true}, "forum_facebook_key": "", "use_yahoo": true, "subscribed": false, "active_gargoyle_switches": ["edits_to_spam", "es_index_threads", "firehose_gnip", "firehose_gnip_http", "git_themes", "html_email", "limit_get_posts_days_30d", "listactivity_replies", "listactivity_replies_30d", "moderate_ascending", "new_moderate", "olark_addons", "olark_admin_addons", "olark_admin_packages", "olark_install", "olark_support", "phoenix", "realtime", "redis_threadcount", "send_to_impermium", "show_captcha_on_links", "stats", "statsd.timings", "theme_editor_disabled", "train_impermium", "use_impermium", "use_master_for_api", "vip_read_slave"], "realtime_speed": 15000, "use_openid": true}}; /* */
    /* */ cookieMessages = {"user_created": null, "post_has_profile": null, "post_twitter": null, "post_not_approved": null}; session = {"url": null, "name": null, "email": null}; /* */

    DISQUS.jsonData = jsonData;
    DISQUS.jsonData.cookie_messages = cookieMessages;
    DISQUS.jsonData.session = session;

    if (DISQUS.useSSL) {
        DISQUS.useSSL(DISQUS.jsonData.settings);
    }

    // The mappings below are for backwards compatibility--before we port all the code that
    // accesses jsonData.settings to DISQUS.settings

    var mappings = {
        debug:                'disqus.debug',
        minify_js:            'disqus.minified',
        read_only:            'disqus.readonly',
        recaptcha_public_key: 'disqus.recaptcha.key',
        facebook_app_id:      'disqus.facebook.appId',
        facebook_api_key:     'disqus.facebook.apiKey'
    };

    var urlMappings = {
        disqus_url:    'disqus.urls.main',
        media_url:     'disqus.urls.media',
        ssl_media_url: 'disqus.urls.sslMedia',
        realtime_url:  'disqus.urls.realtime',
        uploads_url:   'disqus.urls.uploads'
    };

    if (DISQUS.jsonData.context.switches.realtime_setting_change) {
        urlMappings.realtimeHost = 'realtime.host';
        urlMappings.realtimePort = 'realtime.port';
    }
    for (key in mappings) {
        if (mappings.hasOwnProperty(key)) {
            DISQUS.settings.set(mappings[key], DISQUS.jsonData.settings[key]);
        }
    }

    for (key in urlMappings) {
        if (urlMappings.hasOwnProperty(key)) {
            DISQUS.jsonData.settings[key] = DISQUS.settings.get(urlMappings[key]);
        }
    }
}());

DISQUS.jsonData.context.csrf_token = '21bc467119200cb06806902fa8e2f5b0';

DISQUS.jsonData.urls = {
    login: 'http://disqus.com/profile/login/',
    logout: 'http://disqus.com/logout/',
    upload_remove: 'http://micahcarrick.disqus.com/thread/avr_3_wire_hd44780_lcd_interface_avr_gcc/async_media_remove/',
    request_user_profile: 'http://disqus.com/AnonymousUser/',
    request_user_avatar: 'http://mediacdn.disqus.com/1325732276/images/noavatar92.png',
    verify_email: 'http://disqus.com/verify/',
    remote_settings: 'http://micahcarrick.disqus.com/_auth/embed/remote_settings/',
    edit_profile_window: 'http://disqus.com/embed/profile/edit/',
    embed_thread: 'http://micahcarrick.disqus.com/thread.js',
    embed_vote: 'http://micahcarrick.disqus.com/vote.js',
    embed_thread_vote: 'http://micahcarrick.disqus.com/thread_vote.js',
    embed_thread_share: 'http://micahcarrick.disqus.com/thread_share.js',
    embed_queueurl: 'http://micahcarrick.disqus.com/queueurl.js',
    embed_hidereaction: 'http://micahcarrick.disqus.com/hidereaction.js',
    embed_more_reactions: 'http://micahcarrick.disqus.com/more_reactions.js',
    embed_subscribe: 'http://micahcarrick.disqus.com/subscribe.js',
    embed_highlight: 'http://micahcarrick.disqus.com/highlight.js',
    embed_block: 'http://micahcarrick.disqus.com/block.js',
    update_moderate_all: 'http://micahcarrick.disqus.com/update_moderate_all.js',
    update_days_alive: 'http://micahcarrick.disqus.com/update_days_alive.js',
    show_user_votes: 'http://micahcarrick.disqus.com/show_user_votes.js',
    forum_view: 'http://micahcarrick.disqus.com/avr_3_wire_hd44780_lcd_interface_avr_gcc',
    cnn_saml_try: 'http://disqus.com/saml/cnn/try/',
    realtime: DISQUS.jsonData.settings.realtime_url,
    thread_view: 'http://micahcarrick.disqus.com/thread/avr_3_wire_hd44780_lcd_interface_avr_gcc/',
    twitter_connect: DISQUS.jsonData.settings.disqus_url + '/_ax/twitter/begin/',
    yahoo_connect: DISQUS.jsonData.settings.disqus_url + '/_ax/yahoo/begin/',
    openid_connect: DISQUS.jsonData.settings.disqus_url + '/_ax/openid/begin/',
    googleConnect: DISQUS.jsonData.settings.disqus_url + '/_ax/google/begin/',
    community: 'http://micahcarrick.disqus.com/community.html',
    admin: 'http://micahcarrick.disqus.com/admin/moderate/',
    moderate: 'http://micahcarrick.disqus.com/admin/moderate/',
    moderate_threads: 'http://micahcarrick.disqus.com/admin/moderate-threads/',
    settings: 'http://micahcarrick.disqus.com/admin/settings/',
    unmerged_profiles: 'http://disqus.com/embed/profile/unmerged_profiles/',

    channels: {
        def:      'http://disqus.com/default.html', /* default channel */
        auth:     'https://disqus.com/embed/login.html',
        tweetbox: 'http://disqus.com/forums/integrations/twitter/tweetbox.html?f=micahcarrick',
        edit:     'http://micahcarrick.disqus.com/embed/editcomment.html'
    }
};


// 
//     
DISQUS.jsonData.urls.channels.reply = 'http://mediacdn.disqus.com/1325732276/build/system/reply.html';
DISQUS.jsonData.urls.channels.upload = 'http://mediacdn.disqus.com/1325732276/build/system/upload.html';
DISQUS.jsonData.urls.channels.sso = 'http://mediacdn.disqus.com/1325732276/build/system/sso.html';
DISQUS.jsonData.urls.channels.facebook = 'http://mediacdn.disqus.com/1325732276/build/system/facebook.html';
//     
// 