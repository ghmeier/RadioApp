local newsView
if (nui:isWebViewAvailable()) then
	newsView = nui:createWebView({
	x=0,y=0,w=director.displayWidth,h=director.isplayHeight,transparentBackground=true,
	url="http://radio.uccs.edu",
	} )
else
	print("get a damn web view")
end

local 

function webViewLoadedEvent(event)
	if (event.type  == "error") then
		print("Error loading web page" .. event.url)
	elseif(event.type == "loaded") then
		print("WebPage Loaded ".. event.url)
	end
end

system:addEventListener("webViewLoaded",webViewLoadedEvent)