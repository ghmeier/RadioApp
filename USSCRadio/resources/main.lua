local fullScene = director:createScene()
fullScene.newsScene = director:createScene()
fullScene.scheduleScene = director:createScene()
local names = {"news","schedule","events"}
fullScene.newsScene.newsView = nui:createWebView({
	x=0,y=0,w=director.deviceWidth,h=200,transparentBackground=true,
	url="http://radio.uccs.edu",
	} )
fullScene.newsScene.scheduleView = nui:createWebView({
	x=0,y=100,w=director.deviceWidth,h=200,transparentBackground=true,
	url="https://www.youtube.com/watch?v=fPevj0vT7-I",
	} )

fullScene.newsScene.newsView.zOrder = -1
fullScene.newsScene.scheduleView.zOrder = 5
fullScene.label = director:createLabel({text="NEWS",x=500,y=0,w=200,h=100})
fullScene.label.color = {255,0,0}
fullScene.label.zOrder = 2
fullScene.newsScene.sprite = director:createSprite(40,40,"textures/HLC.jpg");
fullScene.newsScene.sprite.rotation = -20;
fullScene.newsScene.sprite.xScale = .1
fullScene.newsScene.sprite.yScale = .1
fullScene.newsScene.sprite.color = {255,0,0}
fullScene.newsScene.sprite.zOrder = 3

function webViewLoadedEvent(event)
	if (event.type  == "error") then
		print("Error loading web page" .. event.url)
	elseif(event.type == "loaded") then
		print("WebPage Loaded ".. event.url)
	end
end

system:addEventListener("webViewLoaded",webViewLoadedEvent)