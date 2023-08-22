#
#  Be sure to run `pod spec lint LetsViewIOSSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the s.
#
#  To learn more about Podspec attributes see https://guides.cocoapods.org/syntax/pods.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#
# pod lib lint --allow-warnings --skip-import-validation --verbose
#
# pod trunk push LetsViewIOSSDK.podspec --allow-warnings --skip-import-validation --verbose

Pod::Spec.new do |s|

  s.name         = "LetsViewIOSSDK"
  s.version      = "1.2.0"
  s.summary      = "A short description of LetsViewIOSSDK."

  s.description  = "LetsviewSDK"

  s.homepage     = "https://letsview.com/sdk"

  s.license      = { :type => "Copyright", :text => "Copyright ©2023 Wangxutech.com. All rights reserved.\n"}

  s.author      = { "wangxutech" => "moblie@wangxutech.com" }

  s.source       = { :http => "https://aw.aoscdn.com/base/support/v2/resources/510e6cf7-b7a5-47b0-b347-7e5c92d42634/download", :type => 'zip' }
  
  s.platform = :ios
  s.ios.deployment_target = "11.0"
  s.requires_arc = true
  
  s.default_subspec = "Core"
  
  s.subspec "Core" do |ss|
    ss.vendored_frameworks = [
    'WXMirrorCore.framework',
    ]
    ss.ios.pod_target_xcconfig = {
      'VALID_ARCHS[sdk=iphonesimulator*]' => ''
    }
  end
  
  s.subspec "DLNA" do |ss|
    ss.vendored_frameworks = [
        'WXDLNASender.framework',
    ]
    ss.dependency 'LetsViewIOSSDK/Core'
    ss.libraries = 'xml2'
    ss.ios.pod_target_xcconfig = {
      'VALID_ARCHS[sdk=iphonesimulator*]' => ''
    }
  end
  
  s.subspec "Airplay" do |ss|
    ss.vendored_frameworks = [
        'WXAirplaySender.framework',
    ]
    ss.dependency 'LetsViewIOSSDK/Core'
    ss.ios.pod_target_xcconfig = {
      'VALID_ARCHS[sdk=iphonesimulator*]' => ''
    }
  end
  
  s.subspec "Sender" do |ss|
    ss.vendored_frameworks = [
        'WXCastiOSSender.framework',
    ]
    ss.dependency 'MMWormhole'
    ss.dependency 'LetsViewIOSSDK/Core'
    ss.ios.pod_target_xcconfig = {
      'VALID_ARCHS[sdk=iphonesimulator*]' => ''
    }
  end
  
  s.subspec "Receiver" do |ss|
    ss.vendored_frameworks = [
        'WXCastiOSReceiver.framework',
        'WXCastFFMpeg.framework',
    ]
    ss.dependency 'LetsViewIOSSDK/Core'
    ss.ios.pod_target_xcconfig = {
      'VALID_ARCHS[sdk=iphonesimulator*]' => ''
    }
  end
end
