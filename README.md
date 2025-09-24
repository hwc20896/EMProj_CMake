## 關於
這是一個基於 Qt 的桌面應用程式，旨在幫助用戶學習和測試對《中華人民共和國憲法》和《澳門特別行政區基本法》的了解。  
初代版本的儲存庫在<https://github.com/hwc20896/Moral-Education-Project---Game-Design>。

> [!CAUTION]
> 此程序不兼容於 Windows 7 及以下版本。

---

## 下載方法
到旁邊[Releases](https://github.com/hwc20896/ChineseProj_CMake/releases)那裏下載最新版本，解壓了找到並雙擊`EMProj.exe`即可。
> [!IMPORTANT]
> 第一次打開可能會自動把程序釘選到任務欄，且試圖取消釘選時會導致`explorer.exe`崩潰。
> 解決方法：等待`explorer.exe`重啓後再次嘗試取消勾選。
> 作者正在努力修復這個問題。

---

## 玩法
每輪遊戲可選擇不同模式（全部題目、僅基本法、僅憲法），系統會隨機抽取 4 題。  
玩家需依次作答，答對可進入下一題並播放恭喜音效，答錯則顯示正確答案並播放鼓勵音效。
基本法題庫共 9 題，憲法題庫共 13 題，每輪將隨機抽出 4 題進行遊戲。

> [!NOTE]
> 在[v1](https://github.com/hwc20896/EMProj_CMake/releases/tag/v1)及以前，系統會抽出 8 題進行遊戲。

> [!TIP]
> 背景音樂預設為關閉狀態，玩家可在上方的「聲音按鈕」以啓用。
> 只有在答題過程中，背景音樂才會播放。

---

## 如果你想要Clone這個項目
1. 確保你已經安裝了CMake、vcpkg和Qt6.9.0（MinGW、Qt Multimedia）。
2. 透過vcpkg安裝`sqlite-modern-cpp`庫，並確保在系統變數中添加了vcpkg的路徑。
3. Clone這個項目到本地。
   ```bash
   git clone https://github.com/hwc20896/EMProj_CMake.git
   ```
4. 使用一個IDE（例如CLion）打開這個項目。
5. 配置CMake，確保CMake能找到Qt 6.9.0（如`PATH=D:\QT\6.9.0\mingw_64\bin`），  
   並在CMake選項中添加`-DCMAKE_TOOLCHAIN_FILE=${你的vcpkg路徑}/scripts/buildsystems/vcpkg.cmake`（可選，視乎CMake是否報錯）。