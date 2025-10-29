/***********************************************
/gen auto by zuitools
***********************************************/
#include "DvrPlayActivity.h"

/*TAG:GlobalVariable全局变量*/
static ZKTextView* mTextView2Ptr;
static ZKTextView* mTextView1Ptr;
static ZKWindow* mWindowLeftPtr;
static ZKTextView* mTextViewbgPtr;
static ZKButton* mButtonPlayDeletePtr;
static ZKButton* mButtonNextPtr;
static ZKButton* mButtonPrevPtr;
static ZKButton* mButtonLockPtr;
static ZKTextView* mTextViewPhotoPtr;
static ZKTextView* mTextViewPlayFilePtr;
static ZKButton* mButtonPausePtr;
static ZKTextView* mTextViewProgressBgPtr;
static ZKTextView* mTextViewProgressPtr;
static ZKWindow* mWindowProgressPtr;
static ZKWindow* mWindowPlayPtr;
static ZKTextView* mTextViewDurationPtr;
static ZKTextView* mTextViewElapsePtr;
static ZKSeekBar* mSeekBarProgressPtr;
static ZKButton* mButton2Ptr;
static ZKButton* mButton1Ptr;
static ZKRadioGroup* mRadioGroupTypePtr;
static ZKButton* mButtonDeletePtr;
static ZKButton* mButtonSelectPtr;
static ZKButton* mButtonViewPtr;
static ZKWindow* mWindowRightPtr;
static ZKListView* mListViewFilePtr;
static ZKVideoView* mVideoView1Ptr;
static DvrPlayActivity* mActivityPtr;

/*register activity*/
REGISTER_ACTIVITY(DvrPlayActivity);

typedef struct {
	int id; // 定时器ID ， 不能重复
	int time; // 定时器  时间间隔  单位 毫秒
}S_ACTIVITY_TIMEER;

#include "logic/DvrPlayLogic.cc"

/***********/
typedef struct {
    int id;
    const char *pApp;
} SAppInfo;

/**
 *点击跳转window
 */
static SAppInfo sAppInfoTab[] = {
//  { ID_MAIN_TEXT, "TextViewActivity" },
};

/***************/
typedef bool (*ButtonCallback)(ZKButton *pButton);
/**
 * button onclick表
 */
typedef struct {
    int id;
    ButtonCallback callback;
}S_ButtonCallback;

/*TAG:ButtonCallbackTab按键映射表*/
static S_ButtonCallback sButtonCallbackTab[] = {
    ID_DVRPLAY_ButtonPlayDelete, onButtonClick_ButtonPlayDelete,
    ID_DVRPLAY_ButtonNext, onButtonClick_ButtonNext,
    ID_DVRPLAY_ButtonPrev, onButtonClick_ButtonPrev,
    ID_DVRPLAY_ButtonLock, onButtonClick_ButtonLock,
    ID_DVRPLAY_ButtonPause, onButtonClick_ButtonPause,
    ID_DVRPLAY_Button2, onButtonClick_Button2,
    ID_DVRPLAY_Button1, onButtonClick_Button1,
    ID_DVRPLAY_ButtonDelete, onButtonClick_ButtonDelete,
    ID_DVRPLAY_ButtonSelect, onButtonClick_ButtonSelect,
    ID_DVRPLAY_ButtonView, onButtonClick_ButtonView,
};
/***************/


typedef void (*SeekBarCallback)(ZKSeekBar *pSeekBar, int progress);
typedef struct {
    int id;
    SeekBarCallback callback;
}S_ZKSeekBarCallback;
/*TAG:SeekBarCallbackTab*/
static S_ZKSeekBarCallback SZKSeekBarCallbackTab[] = {
    ID_DVRPLAY_SeekBarProgress, onProgressChanged_SeekBarProgress,
};


typedef int (*ListViewGetItemCountCallback)(const ZKListView *pListView);
typedef void (*ListViewobtainListItemDataCallback)(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index);
typedef void (*ListViewonItemClickCallback)(ZKListView *pListView, int index, int id);
typedef struct {
    int id;
    ListViewGetItemCountCallback getListItemCountCallback;
    ListViewobtainListItemDataCallback obtainListItemDataCallback;
    ListViewonItemClickCallback onItemClickCallback;
}S_ListViewFunctionsCallback;
/*TAG:ListViewFunctionsCallback*/
static S_ListViewFunctionsCallback SListViewFunctionsCallbackTab[] = {
    ID_DVRPLAY_ListViewFile, getListItemCount_ListViewFile, obtainListItemData_ListViewFile, onListItemClick_ListViewFile,
};


typedef void (*SlideWindowItemClickCallback)(ZKSlideWindow *pSlideWindow, int index);
typedef struct {
    int id;
    SlideWindowItemClickCallback onSlideItemClickCallback;
}S_SlideWindowItemClickCallback;
/*TAG:SlideWindowFunctionsCallbackTab*/
static S_SlideWindowItemClickCallback SSlideWindowItemClickCallbackTab[] = {
};


typedef void (*EditTextInputCallback)(const std::string &text);
typedef struct {
    int id;
    EditTextInputCallback onEditTextChangedCallback;
}S_EditTextInputCallback;
/*TAG:EditTextInputCallback*/
static S_EditTextInputCallback SEditTextInputCallbackTab[] = {
};

typedef void (*VideoViewCallback)(ZKVideoView *pVideoView, int msg);
typedef struct {
    int id; //VideoView ID
    bool loop; // 是否是轮播类型
    int defaultvolume;//轮播类型时,默认视频音量
    VideoViewCallback onVideoViewCallback;
}S_VideoViewCallback;
/*TAG:VideoViewCallback*/
static S_VideoViewCallback SVideoViewCallbackTab[] = {
    ID_DVRPLAY_VideoView1, false, 5, onVideoViewPlayerMessageListener_VideoView1,
};


typedef void (*RadioGroupCallback)(ZKRadioGroup*, int);
typedef struct {
  int id;
  RadioGroupCallback onCheckedChanged;
}S_RadioGroupCallback;
/*TAG:RadioGroupCallbackTab*/
static S_RadioGroupCallback SRadioGroupCallbackTab[] = {
    ID_DVRPLAY_RadioGroupType, onCheckedChanged_RadioGroupType,
};

DvrPlayActivity::DvrPlayActivity() {
	//todo add init code here
	mVideoLoopIndex = -1;
	mVideoLoopErrorCount = 0;
}

DvrPlayActivity::~DvrPlayActivity() {
  //todo add init file here
  // 退出应用时需要反注册
    EASYUICONTEXT->unregisterGlobalTouchListener(this);
    unregisterProtocolDataUpdateListener(onProtocolDataUpdate);
    onUI_quit();
    mActivityPtr = NULL;
    mTextView2Ptr = NULL;
    mTextView1Ptr = NULL;
    mWindowLeftPtr = NULL;
    mTextViewbgPtr = NULL;
    mButtonPlayDeletePtr = NULL;
    mButtonNextPtr = NULL;
    mButtonPrevPtr = NULL;
    mButtonLockPtr = NULL;
    mTextViewPhotoPtr = NULL;
    mTextViewPlayFilePtr = NULL;
    mButtonPausePtr = NULL;
    mTextViewProgressBgPtr = NULL;
    mTextViewProgressPtr = NULL;
    mWindowProgressPtr = NULL;
    mWindowPlayPtr = NULL;
    mTextViewDurationPtr = NULL;
    mTextViewElapsePtr = NULL;
    mSeekBarProgressPtr = NULL;
    mButton2Ptr = NULL;
    mButton1Ptr = NULL;
    mRadioGroupTypePtr = NULL;
    mButtonDeletePtr = NULL;
    mButtonSelectPtr = NULL;
    mButtonViewPtr = NULL;
    mWindowRightPtr = NULL;
    mListViewFilePtr = NULL;
    mVideoView1Ptr = NULL;
}

const char* DvrPlayActivity::getAppName() const{
	return "DvrPlay.ftu";
}

//TAG:onCreate
void DvrPlayActivity::onCreate() {
	Activity::onCreate();
    mTextView2Ptr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextView2);
    mTextView1Ptr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextView1);
    mWindowLeftPtr = (ZKWindow*)findControlByID(ID_DVRPLAY_WindowLeft);
    mTextViewbgPtr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextViewbg);
    mButtonPlayDeletePtr = (ZKButton*)findControlByID(ID_DVRPLAY_ButtonPlayDelete);
    mButtonNextPtr = (ZKButton*)findControlByID(ID_DVRPLAY_ButtonNext);
    mButtonPrevPtr = (ZKButton*)findControlByID(ID_DVRPLAY_ButtonPrev);
    mButtonLockPtr = (ZKButton*)findControlByID(ID_DVRPLAY_ButtonLock);
    mTextViewPhotoPtr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextViewPhoto);
    mTextViewPlayFilePtr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextViewPlayFile);
    mButtonPausePtr = (ZKButton*)findControlByID(ID_DVRPLAY_ButtonPause);
    mTextViewProgressBgPtr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextViewProgressBg);
    mTextViewProgressPtr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextViewProgress);
    mWindowProgressPtr = (ZKWindow*)findControlByID(ID_DVRPLAY_WindowProgress);
    mWindowPlayPtr = (ZKWindow*)findControlByID(ID_DVRPLAY_WindowPlay);
    mTextViewDurationPtr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextViewDuration);
    mTextViewElapsePtr = (ZKTextView*)findControlByID(ID_DVRPLAY_TextViewElapse);
    mSeekBarProgressPtr = (ZKSeekBar*)findControlByID(ID_DVRPLAY_SeekBarProgress);if(mSeekBarProgressPtr!= NULL){mSeekBarProgressPtr->setSeekBarChangeListener(this);}
    mButton2Ptr = (ZKButton*)findControlByID(ID_DVRPLAY_Button2);
    mButton1Ptr = (ZKButton*)findControlByID(ID_DVRPLAY_Button1);
    mRadioGroupTypePtr = (ZKRadioGroup*)findControlByID(ID_DVRPLAY_RadioGroupType);if(mRadioGroupTypePtr!= NULL){mRadioGroupTypePtr->setCheckedChangeListener(this);}
    mButtonDeletePtr = (ZKButton*)findControlByID(ID_DVRPLAY_ButtonDelete);
    mButtonSelectPtr = (ZKButton*)findControlByID(ID_DVRPLAY_ButtonSelect);
    mButtonViewPtr = (ZKButton*)findControlByID(ID_DVRPLAY_ButtonView);
    mWindowRightPtr = (ZKWindow*)findControlByID(ID_DVRPLAY_WindowRight);
    mListViewFilePtr = (ZKListView*)findControlByID(ID_DVRPLAY_ListViewFile);if(mListViewFilePtr!= NULL){mListViewFilePtr->setListAdapter(this);mListViewFilePtr->setItemClickListener(this);}
    mVideoView1Ptr = (ZKVideoView*)findControlByID(ID_DVRPLAY_VideoView1);if(mVideoView1Ptr!= NULL){mVideoView1Ptr->setVideoPlayerMessageListener(this);}
	mActivityPtr = this;
	onUI_init();
  registerProtocolDataUpdateListener(onProtocolDataUpdate);
  rigesterActivityTimer();
}

void DvrPlayActivity::onClick(ZKBase *pBase) {
	//TODO: add widget onClik code 
    int buttonTablen = sizeof(sButtonCallbackTab) / sizeof(S_ButtonCallback);
    for (int i = 0; i < buttonTablen; ++i) {
        if (sButtonCallbackTab[i].id == pBase->getID()) {
            if (sButtonCallbackTab[i].callback((ZKButton*)pBase)) {
            	return;
            }
            break;
        }
    }


    int len = sizeof(sAppInfoTab) / sizeof(sAppInfoTab[0]);
    for (int i = 0; i < len; ++i) {
        if (sAppInfoTab[i].id == pBase->getID()) {
            EASYUICONTEXT->openActivity(sAppInfoTab[i].pApp);
            return;
        }
    }

	Activity::onClick(pBase);
}

void DvrPlayActivity::onResume() {
	Activity::onResume();
	EASYUICONTEXT->registerGlobalTouchListener(this);
	startVideoLoopPlayback();
	onUI_show();
}

void DvrPlayActivity::onPause() {
	Activity::onPause();
	EASYUICONTEXT->unregisterGlobalTouchListener(this);
	stopVideoLoopPlayback();
	onUI_hide();
}

bool DvrPlayActivity::onBack() {
	return onUI_back();
}

void DvrPlayActivity::onIntent(const Intent *intentPtr) {
	Activity::onIntent(intentPtr);
	onUI_intent(intentPtr);
}

bool DvrPlayActivity::onTimer(int id) {
	return onUI_Timer(id);
}

void DvrPlayActivity::onProgressChanged(ZKSeekBar *pSeekBar, int progress){

    int seekBarTablen = sizeof(SZKSeekBarCallbackTab) / sizeof(S_ZKSeekBarCallback);
    for (int i = 0; i < seekBarTablen; ++i) {
        if (SZKSeekBarCallbackTab[i].id == pSeekBar->getID()) {
            SZKSeekBarCallbackTab[i].callback(pSeekBar, progress);
            break;
        }
    }
}

int DvrPlayActivity::getListItemCount(const ZKListView *pListView) const{
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            return SListViewFunctionsCallbackTab[i].getListItemCountCallback(pListView);
            break;
        }
    }
    return 0;
}

void DvrPlayActivity::obtainListItemData(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].obtainListItemDataCallback(pListView, pListItem, index);
            break;
        }
    }
}

void DvrPlayActivity::onItemClick(ZKListView *pListView, int index, int id){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].onItemClickCallback(pListView, index, id);
            break;
        }
    }
}

void DvrPlayActivity::onSlideItemClick(ZKSlideWindow *pSlideWindow, int index) {
    int tablen = sizeof(SSlideWindowItemClickCallbackTab) / sizeof(S_SlideWindowItemClickCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SSlideWindowItemClickCallbackTab[i].id == pSlideWindow->getID()) {
            SSlideWindowItemClickCallbackTab[i].onSlideItemClickCallback(pSlideWindow, index);
            break;
        }
    }
}

bool DvrPlayActivity::onTouchEvent(const MotionEvent &ev) {
    return onDvrPlayActivityTouchEvent(ev);
}

void DvrPlayActivity::onTextChanged(ZKTextView *pTextView, const std::string &text) {
    int tablen = sizeof(SEditTextInputCallbackTab) / sizeof(S_EditTextInputCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SEditTextInputCallbackTab[i].id == pTextView->getID()) {
            SEditTextInputCallbackTab[i].onEditTextChangedCallback(text);
            break;
        }
    }
}

void DvrPlayActivity::rigesterActivityTimer() {
    int tablen = sizeof(REGISTER_ACTIVITY_TIMER_TAB) / sizeof(S_ACTIVITY_TIMEER);
    for (int i = 0; i < tablen; ++i) {
        S_ACTIVITY_TIMEER temp = REGISTER_ACTIVITY_TIMER_TAB[i];
        registerTimer(temp.id, temp.time);
    }
}


void DvrPlayActivity::onVideoPlayerMessage(ZKVideoView *pVideoView, int msg) {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SVideoViewCallbackTab[i].id == pVideoView->getID()) {
        	if (SVideoViewCallbackTab[i].loop) {
                //循环播放
        		videoLoopPlayback(pVideoView, msg, i);
        	} else if (SVideoViewCallbackTab[i].onVideoViewCallback != NULL){
        	    SVideoViewCallbackTab[i].onVideoViewCallback(pVideoView, msg);
        	}
            break;
        }
    }
}

void DvrPlayActivity::videoLoopPlayback(ZKVideoView *pVideoView, int msg, size_t callbackTabIndex) {

	switch (msg) {
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED\n");
    if (callbackTabIndex >= (sizeof(SVideoViewCallbackTab)/sizeof(S_VideoViewCallback))) {
      break;
    }
		pVideoView->setVolume(SVideoViewCallbackTab[callbackTabIndex].defaultvolume / 10.0);
		mVideoLoopErrorCount = 0;
		break;
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_ERROR:
		/**错误处理 */
		++mVideoLoopErrorCount;
		if (mVideoLoopErrorCount > 100) {
			LOGD("video loop error counts > 100, quit loop playback !");
            break;
		} //不用break, 继续尝试播放下一个
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED\n");
        std::vector<std::string> videolist;
        std::string fileName(getAppName());
        if (fileName.size() < 4) {
             LOGD("getAppName size < 4, ignore!");
             break;
        }
        fileName = fileName.substr(0, fileName.length() - 4) + "_video_list.txt";
        fileName = "/mnt/extsd/" + fileName;
        if (!parseVideoFileList(fileName.c_str(), videolist)) {
            LOGD("parseVideoFileList failed !");
		    break;
        }
		if (pVideoView && !videolist.empty()) {
			mVideoLoopIndex = (mVideoLoopIndex + 1) % videolist.size();
			pVideoView->play(videolist[mVideoLoopIndex].c_str());
		}
		break;
	}
}

void DvrPlayActivity::startVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		//循环播放
    		videoLoopPlayback(videoView, ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED, i);
    		return;
    	}
    }
}

void DvrPlayActivity::stopVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		if (videoView->isPlaying()) {
    		    videoView->stop();
    		}
    		return;
    	}
    }
}

bool DvrPlayActivity::parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList) {
	mediaFileList.clear();
	if (NULL == pFileListPath || 0 == strlen(pFileListPath)) {
        LOGD("video file list is null!");
		return false;
	}

	ifstream is(pFileListPath, ios_base::in);
	if (!is.is_open()) {
		LOGD("cann't open file %s \n", pFileListPath);
		return false;
	}
	char tmp[1024] = {0};
	while (is.getline(tmp, sizeof(tmp))) {
		string str = tmp;
		removeCharFromString(str, '\"');
		removeCharFromString(str, '\r');
		removeCharFromString(str, '\n');
		if (str.size() > 1) {
     		mediaFileList.push_back(str.c_str());
		}
	}
  LOGD("(f:%s, l:%d) parse fileList[%s], get [%d]files", __FUNCTION__,
      __LINE__, pFileListPath, int(mediaFileList.size()));
  for (std::vector<string>::size_type i = 0; i < mediaFileList.size(); i++) {
    LOGD("file[%u]:[%s]", ::size_t(i), mediaFileList[i].c_str());
  }
	is.close();

	return true;
}

int DvrPlayActivity::removeCharFromString(string& nString, char c) {
    string::size_type   pos;
    while(1) {
        pos = nString.find(c);
        if(pos != string::npos) {
            nString.erase(pos, 1);
        } else {
            break;
        }
    }
    return (int)nString.size();
}

void DvrPlayActivity::registerUserTimer(int id, int time) {
	registerTimer(id, time);
}

void DvrPlayActivity::unregisterUserTimer(int id) {
	unregisterTimer(id);
}

void DvrPlayActivity::resetUserTimer(int id, int time) {
	resetTimer(id, time);
}
void DvrPlayActivity::onCheckedChanged(ZKRadioGroup* pRadioGroup, int checkedID) {
    int tablen = sizeof(SRadioGroupCallbackTab) / sizeof(S_RadioGroupCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SRadioGroupCallbackTab[i].id == pRadioGroup->getID()) {
        	SRadioGroupCallbackTab[i].onCheckedChanged(pRadioGroup, checkedID);
            break;
        }
    }
}