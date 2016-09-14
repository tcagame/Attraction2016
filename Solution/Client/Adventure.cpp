#include "Adventure.h"

Adventure::Adventure( ) {
	_type = TYPE_NONE;
	_contents[ TYPE_KNIGHT_CREATE ]               = Content( CHARACTER_KNIGHT, "さあいこう…世界のために！"                                                                                                   , Sound::VOICE_KNIGHT_LOGIN         );
	_contents[ TYPE_KNIGHT_WAIT ]                 = Content( CHARACTER_KNIGHT, "早くいこう、でなければ世界が滅びてしまう！"                                                                                   , Sound::VOICE_KNIGHT_WAIT		  );
	_contents[ TYPE_KNIGHT_STORE ]                = Content( CHARACTER_KNIGHT, "この一撃にかける！"                                                                                                           , Sound::VOICE_KNIGHT_STORE         );
	_contents[ TYPE_KNIGHT_DEATHBLOW ]            = Content( CHARACTER_KNIGHT, "この剣とともに・・・お前を倒す！"                                                                                             , Sound::VOICE_KNIGHT_DEATHBLOW     );
	_contents[ TYPE_KNIGHT_ANOTHER_DEAD ]         = Content( CHARACTER_KNIGHT, "お前がいたからここまでこられたのに…"                                                                                         , Sound::VOICE_KNIGHT_ANOTHER_DEATH );
	_contents[ TYPE_KNIGHT_PINCH ]                = Content( CHARACTER_KNIGHT, "クッ！このままではッ！"                                                                                                       , Sound::VOICE_KNIGHT_PINCH         );
	_contents[ TYPE_KNIGHT_DEAD ]                 = Content( CHARACTER_KNIGHT, "俺が倒れては…せか…い…は……"                                                                                               , Sound::VOICE_KNIGHT_CLEAR         );
	_contents[ TYPE_KNIGHT_CLEAR ]                = Content( CHARACTER_KNIGHT, "これで世界が平和になった！もう怯えて過ごす日々は終わりだ！"                                                                   , Sound::VOICE_KNIGHT_DEAD          );
											      																						                                                                      
	_contents[ TYPE_MONK_CREATE ]                 = Content( CHARACTER_MONK, "俺様が最強だってこと証明してやる！"                                                                                             , Sound::VOICE_MONK_LOGIN         );
	_contents[ TYPE_MONK_WAIT ]                   = Content( CHARACTER_MONK, "速くヤッちまおうぜ！"                                                                                                           , Sound::VOICE_MONK_WAIT		    );
	_contents[ TYPE_MONK_STORE ]                  = Content( CHARACTER_MONK, "本気……だしちゃうよ！！"                                                                                                       , Sound::VOICE_MONK_STORE         );
	_contents[ TYPE_MONK_DEATHBLOW ]              = Content( CHARACTER_MONK, "オリャオリャオリャオリャ…オリャー！"                                                                                           , Sound::VOICE_MONK_DEATHBLOW     );
	_contents[ TYPE_MONK_ANOTHER_DEAD ]           = Content( CHARACTER_MONK, "お前が弱かった…ただそれだけさ……"                                                                                             , Sound::VOICE_MONK_ANOTHER_DEATH );
	_contents[ TYPE_MONK_PINCH ]                  = Content( CHARACTER_MONK, "やべぇな、やられちまう"                                                                                                         , Sound::VOICE_MONK_PINCH         );
	_contents[ TYPE_MONK_DEAD ]                   = Content( CHARACTER_MONK, "ヤル前にヤられるとはな…"                                                                                                       , Sound::VOICE_MONK_CLEAR         );
	_contents[ TYPE_MONK_CLEAR ]                  = Content( CHARACTER_MONK, "やっぱオレは最強だな！それを証明してやったぜ！"                                                                                 , Sound::VOICE_MONK_DEAD          );
											      																						                                                                      
	_contents[ TYPE_HUNTER_CREATE ]               = Content( CHARACTER_HUNTER, "今日もひと狩りいきますか！"				                                                                                      , Sound::VOICE_HUNTER_LOGIN         );
	_contents[ TYPE_HUNTER_WAIT ]                 = Content( CHARACTER_HUNTER, "速くしようぜ、金が逃げちまう！"                                                                                               , Sound::VOICE_HUNTER_WAIT		  );
	_contents[ TYPE_HUNTER_STORE ]                = Content( CHARACTER_HUNTER, "俺の銃弾、避けられるかい？"                                                                                               , Sound::VOICE_HUNTER_STORE         );
	_contents[ TYPE_HUNTER_DEATHBLOW ]            = Content( CHARACTER_HUNTER, "まぁ、無理だと思うけどね"																				                              , Sound::VOICE_HUNTER_DEATHBLOW     );
	_contents[ TYPE_HUNTER_ANOTHER_DEAD ]         = Content( CHARACTER_HUNTER, "せっかく大儲けしていたのに、ここでハズレを引くとは…もったいない…"                                                           , Sound::VOICE_HUNTER_ANOTHER_DEATH );
	_contents[ TYPE_HUNTER_PINCH ]                = Content( CHARACTER_HUNTER, "やべぇな…金で何とかならないか？"                                                                                             , Sound::VOICE_HUNTER_PINCH         );
	_contents[ TYPE_HUNTER_DEAD ]                 = Content( CHARACTER_HUNTER, "クッ…こんなところで金に逃げられるとは…な…"                                                                                 , Sound::VOICE_HUNTER_CLEAR         );
	_contents[ TYPE_HUNTER_CLEAR ]                = Content( CHARACTER_HUNTER, "これでおしまいかい？これだけ稼いだら一生遊んで暮らせるな！！"                                                                 , Sound::VOICE_HUNTER_DEAD          );
											      																								                                                              
	_contents[ TYPE_WITCH_CREATE ]                = Content( CHARACTER_WITCH, "さあ、魔法陣を完成させるためにいきましょう。"                                                                                  , Sound::VOICE_WITCH_LOGIN         );
	_contents[ TYPE_WITCH_WAIT ]                  = Content( CHARACTER_WITCH, "なに迷っているの？人を…世界を救うための戦いよ！"                                                                              , Sound::VOICE_WITCH_WAIT			 );
	_contents[ TYPE_WITCH_STORE ]                 = Content( CHARACTER_WITCH, "いきますわよ…極大魔法！"                                                                                                      , Sound::VOICE_WITCH_STORE         );
	_contents[ TYPE_WITCH_DEATHBLOW ]             = Content( CHARACTER_WITCH, "ファル・シャレスティーン！"                                                                                                    , Sound::VOICE_WITCH_DEATHBLOW     );
	_contents[ TYPE_WITCH_ANOTHER_DEAD ]          = Content( CHARACTER_WITCH, "ウソ！？治癒魔法が効かない？？"                                                                                                , Sound::VOICE_WITCH_ANOTHER_DEATH );
	_contents[ TYPE_WITCH_PINCH ]                 = Content( CHARACTER_WITCH, "大丈夫、まだ戦えるわ！"                                                                                                        , Sound::VOICE_WITCH_PINCH         );
	_contents[ TYPE_WITCH_DEAD ]                  = Content( CHARACTER_WITCH, "私の魔法はこんなものなの？"                                                                                                    , Sound::VOICE_WITCH_CLEAR         );
	_contents[ TYPE_WITCH_CLEAR ]                 = Content( CHARACTER_WITCH, "これで少しは偉大なる魔法使いに近づいたかな？"                                                                                  , Sound::VOICE_WITCH_DEAD          );
											      														                   							                                                          
	_contents[ TYPE_COMMON_AFTER_LOGIN ]          = Content( CHARACTER_FAIRY, "あなたが勇者様？私の力であなたを強くするからこの世界を一緒に救って！"                                                          , Sound::VOICE_FAIRY_PLAYER_LOGIN );
	_contents[ TYPE_COMMON_TUTORIAL_1 ]           = Content( CHARACTER_FAIRY, "操作方法は簡単！左スティックでキャラクターを移動させることができるわ"                                                          , Sound::VOICE_FAIRY_TUTORIAL_1 );
	_contents[ TYPE_COMMON_TUTORIAL_2 ]           = Content( CHARACTER_FAIRY, "左ボタンで攻撃ができるわ！ 敵をガンガン倒しちゃって！！"                                                                       , Sound::VOICE_FAIRY_TUTORIAL_2 );
	_contents[ TYPE_COMMON_TUTORIAL_3 ]           = Content( CHARACTER_FAIRY, "必殺技を使えるようになったね、右ボタンで必殺技を発動して敵を薙ぎ払っちゃえ！"                                                  , Sound::VOICE_FAIRY_TUTORIAL_4 );
	_contents[ TYPE_COMMON_PLAYER_DEAD ]          = Content( CHARACTER_FAIRY, "ウソ…あなたが倒れてしまっては誰がこの世界を救うの…？ダメ！目を覚まして―！"                                                  , Sound::VOICE_FAIRY_PLAYER_DEAD );
	_contents[ TYPE_COMMON_ANOTHER_PLAYER_LOGIN ] = Content( CHARACTER_FAIRY, "あなたの活躍を見て仲間がこの世界に召喚されたみたい！"                                                                          , Sound::VOICE_FAIRY_ANOTHER_PLAYER_LOGIN );
	_contents[ TYPE_COMMON_LIVE_MONITOR ]         = Content( CHARACTER_FAIRY, "あなたの活躍が認められたみたい！大きなモニターに映っているから、頑張って！！"                                                  , Sound::VOICE_FAIRY_LIVEMONITOR );
	_contents[ TYPE_COMMON_ANOTHER_PLAYER_DEAD ]  = Content( CHARACTER_FAIRY, "あちゃ～味方やられちゃったみたい。ここからは残の勇者でドラゴンを倒すしかないわ！"                                            , Sound::VOICE_FAIRY_ANOTHER_PLAYER_DEAD );
	_contents[ TYPE_COMMON_ARMOR_CONTACT ]        = Content( CHARACTER_FAIRY, "あのゴブリンいつもと違うわ、赤いだけじゃなくて…強そうで…なんか気持ち悪いわね"                                                , Sound::VOICE_FAIRY_ARMOR_CONTACT );
	_contents[ TYPE_COMMON_CYCLOPS_CONTACT ]      = Content( CHARACTER_FAIRY, "あわわ～ゴブリンより強そうなのが現れたわ、気を付けて戦うのよ！"                                                                , Sound::VOICE_FAIRY_CYCLOPS_CONTACT );
	_contents[ TYPE_COMMON_GHOST_CONTACT ]        = Content( CHARACTER_FAIRY, "なんだか火の塊みたいのが現れたわ！あれにあたってしまったら大ダメージよ！"                                                      , Sound::VOICE_FAIRY_GHOST_CONTACT );
	_contents[ TYPE_COMMON_MINOTAUR_ENTRY_1 ]     = Content( CHARACTER_MINOTAUR, "主の元にはいかせない、ここで死んでもらおうか"                                                                               , Sound::VOICE_MINOTAUR_ENTRY_1 );
	_contents[ TYPE_COMMON_MINOTAUR_ENTRY_2 ]     = Content( CHARACTER_MINOTAUR, "ずいぶんと派手に暴れてくれたなぁ、、、それもこれまでだ！"                                                                   , Sound::VOICE_MINOTAUR_ENTRY_2 );
	_contents[ TYPE_COMMON_AFTER_MINOTAUR_ENTRY ] = Content( CHARACTER_FAIRY, "なんだか普通の敵とは違う動きね…あいつの攻撃はかなり強いかも！気を付けて！！"                                                  , Sound::VOICE_FAIRY_MINOTAUR_CONTACT );
	_contents[ TYPE_COMMON_MINOTAUR_ATTACK ]      = Content( CHARACTER_FAIRY, "このミノタウロス賢すぎるし強い！！この動きって…もしかして同じ人間？"                                                          , Sound::VOICE_FAIRY_MINOTAUR_ATTACK );
	_contents[ TYPE_COMMON_MINOTAUR_PINCH ]       = Content( CHARACTER_MINOTAUR, "そろそろ本気を出さないとまずいなぁ"                                                                                         , Sound::VOICE_MINOTAUR_PINCH );
	_contents[ TYPE_COMMON_MINOTAUR_DEAD ]        = Content( CHARACTER_MINOTAUR, "主のもとにいくのか？ならばこれだけは覚えておけ…力を合わせないと、死ぬぞ…"                                                 , Sound::VOICE_MINOTAUR_DEAD_1 );
	_contents[ TYPE_COMMON_AFTER_MINOTAUR_DEAD ]  = Content( CHARACTER_FAIRY, "何とか倒せたわね、でもこれからが本番！さあドラゴンを倒しに行こう！"                                                            , Sound::VOICE_FAIRY_MINOTAUR_DEAD );
	_contents[ TYPE_COMMON_LETS_MOVEING ]         = Content( CHARACTER_FAIRY, "あなたのおかげで魔法陣は完成したわ…もしキミがいいというのなら…この先のドラゴンを一緒に倒してくれませんか？"                  , Sound::VOICE_FAIRY_HAVE_CRYSTAL_4 );
	_contents[ TYPE_COMMON_AFTER_LETS_MOVEING ]   = Content( CHARACTER_FAIRY, "ありがとう。あなたの決断はこの世界において最善の決断よ…さぁドラゴンを倒しに行きましょう！"                                    , Sound::VOICE_FAIRY_HAVE_CRYSTAL_5 );
	_contents[ TYPE_COMMON_HUNT_BOSS ]            = Content( CHARACTER_FAIRY, "これからドラゴンとの戦いね、準備は大丈夫？さぁ気合を入れていきましょう！"                                                      , Sound::VOICE_FAIRY_BIG_CRYSTAL_NEAR );
	_contents[ TYPE_COMMON_TUTORIAL_4 ]           = Content( CHARACTER_FAIRY, "まずはドラゴンをこの世界に留めておくためにクリスタルを３つ集めましょう！"                                                      , Sound::VOICE_FAIRY_HAVE_CRYSTAL_0 );
	_contents[ TYPE_COMMON_HAVE_CRYSTAL_0 ]       = Content( CHARACTER_FAIRY, "クリスタル収集は順調のようね！この調子であと２つ集めましょう！"                                                                , Sound::VOICE_FAIRY_HAVE_CRYSTAL_1 );
	_contents[ TYPE_COMMON_HAVE_CRYSTAL_1 ]       = Content( CHARACTER_FAIRY, "クリスタルが2つ集まったようね、魔法陣の中心に行ってみましょう！"                                                              , Sound::VOICE_FAIRY_HAVE_CRYSTAL_2 );
	_contents[ TYPE_COMMON_HAVE_CRYSTAL_2 ]       = Content( CHARACTER_FAIRY, "クリスタルが3つ集まったようね、魔法陣の中心に行ってみましょう！"                                                              , Sound::VOICE_FAIRY_HAVE_CRYSTAL_3 );
	_contents[ TYPE_COMMON_BEFORE_BOSS_1 ]        = Content( CHARACTER_FAIRY, "現在この世界は、ドラゴンを倒すために魔法陣を作っているわ"                                                                      , Sound::VOICE_FAIRY_EXPLANATION_1 );
	_contents[ TYPE_COMMON_BEFORE_BOSS_2 ]        = Content( CHARACTER_FAIRY, "しかし魔法陣の完成を妨害するためにドラゴンは邪悪な手下を呼びだし私たちの妨害をしているの！"                                    , Sound::VOICE_FAIRY_EXPLANATION_2 );
	_contents[ TYPE_COMMON_BEFORE_BOSS_3 ]        = Content( CHARACTER_FAIRY, "そこで勇者様にはこの手下を倒し魔法陣の完成を手伝ってほしいの"                                                                  , Sound::VOICE_FAIRY_EXPLANATION_3 );
	_contents[ TYPE_COMMON_BOSS_ENTRY ]           = Content( CHARACTER_NONE, "待っていたぞ、小人ども！貴様らを絶望の底に追いやってやる！"                                                                     , Sound::VOICE_BOSS_ENTRY );
	_contents[ TYPE_COMMON_AFTER_BOSS_ENTRY ]     = Content( CHARACTER_FAIRY, "あれがこの世界の元凶…恐ろしいほどの圧力、でもあなたならやれるわ！"                                                            , Sound::VOICE_FAIRY_BOSS_ENTRY );
	_contents[ TYPE_COMMON_BOSS_PINCH_1 ]         = Content( CHARACTER_NONE, "少し遊ばせておればいい気になりおって！"                                                                                         , Sound::VOICE_BOSS_PINCH_1 );
	_contents[ TYPE_COMMON_BOSS_PINCH_2 ]         = Content( CHARACTER_NONE, "貴様らがどれだけ非力で弱いかを思い知らせてやる！"                                                                               , Sound::VOICE_BOSS_PINCH_2 );
	_contents[ TYPE_COMMON_AFTER_BOSS_PINCH ]     = Content( CHARACTER_FAIRY, "これがドラゴンの力…でもダメージを与えられているわ！あとすこし、力を合わせて倒しましょう！"                                    , Sound::VOICE_FAIRY_BOSS_HP_15_PERCENT );
	_contents[ TYPE_COMMON_BOSS_DEAD ]            = Content( CHARACTER_NONE, "この俺を倒したか…しかし光があれば闇もある,再び私のような存在が現れるであろう…世界はこうも美しかったのか……"                  , Sound::VOICE_BOSS_DEAD );
	_contents[ TYPE_COMMON_AFTER_BOSS_DEAD ]      = Content( CHARACTER_FAIRY, "やったー！とうとうドラゴンを倒せた！あなたのおかげで世界が救われるのね！"                                                      , Sound::VOICE_FAIRY_BOSS_DEAD );
	_contents[ TYPE_COMMON_CLEAR ]                = Content( CHARACTER_FAIRY, "あなたがこの世界に現れなかったらあのドラゴンは倒せなかったわ、ありがとう"                                                      , Sound::VOICE_FAIRY_CLEAR_1 );
	_contents[ TYPE_COMMON_AFTER_CLEAR ]          = Content( CHARACTER_FAIRY, "これでお別れね、短い間だったけど楽しかったわ！また会える時が来たらそのときは…平和な世界でね"                                  , Sound::VOICE_FAIRY_CLEAR_2 );
	
	_contents[ TYPE_LIVEMONITOR_WELCOME_1 ]       = Content( CHARACTER_FAIRY, "誰か助けて～、（汗）あ、そこの君！ちょっと待って…待ってってばー！"                                                            , Sound::VOICE_FAIRY_PROLOGUE_1 );
	_contents[ TYPE_LIVEMONITOR_WELCOME_2 ]       = Content( CHARACTER_FAIRY, "この世界はドラゴンを倒さないと滅びてしまうの！だから助けて！！"                                                                , Sound::VOICE_FAIRY_PROLOGUE_2 );
	_contents[ TYPE_LIVEMONITOR_WELCOME_3 ]       = Content( CHARACTER_FAIRY, "現在、この世界にドラゴンが出現中。至急勇者様は目の前のコントローラをとって討伐に向かってください…こんなのでほんとにくるの～？", Sound::VOICE_FAIRY_PROLOGUE_3 );
}


Adventure::~Adventure( ) {
}

void Adventure::start( Adventure::TYPE type ) {
	if ( type == TYPE_NONE ) {
		return;
	}
	_type = type;

	// 対応voiceを流す
	SoundPtr sound = Sound::getTask( );
	sound->playVoice( _contents[ _type ].voice );
}

void Adventure::update( ) {

	SoundPtr sound = Sound::getTask( );
	if ( !sound->isPlayingVoice( ) ) {
		_type = TYPE_NONE;
	}
}

Adventure::CHARACTER Adventure::getCharacter( Adventure::TYPE type ) {
	return _contents[ type ].character;
}

std::string Adventure::getWord( Adventure::TYPE type ) {
	return _contents[ type ].word;
}

Adventure::TYPE Adventure::getType( ) {
	return _type;
}