<template>
	<view>
		<page-head :title="title"></page-head>
			<input class="uni-input"  v-model="stringParam" />
			<view class="uni-btn-v uni-common-mt">
				<button type="primary"  @tap="getToken">初始化 服务器请求获得token</button>
				<button type="primary"  @tap="startLDT">开启人脸检测</button>
			</view>
	</view>
</template>
<script lang="ts">
	import {UTS_Verify,UTS_StartLivingDetect,UTS_Exit,UTS_GetLDTVideo,UTS_RestartLdt,EsLivingDetectResult} from "@/uni_modules/esand-ldt"
	// 定义接口
	interface authSettingInterface {
	  livingType: number;
	  needVideo: boolean;
	  useStrictMode: number;
	}
	
	interface configInterface extends authSettingInterface {
	  returnUrl?: string;
	  cameraDeviceId?: number;
	}
	
	interface HttpResponse {
	  code: number;
	  data: any;
	}
	//token
	let token :string="";
	
	export default {
		data() {
			return {
				title: 'DEMO',
				stringParam:"hello world",
			}
		},
		
		methods: {
			
			/**
			 * 获取初始化token
			 */
			getToken: async function () {
				

				const configData: configInterface = {
				      livingType: 6,
				      needVideo: true,
				      useStrictMode: 1,
				      returnUrl: "https://example.com",
				      cameraDeviceId: 1
				    };
					
					
				let res:EsLivingDetectResult=await UTS_Verify(JSON.stringify(configData));
				
				const url = "https://eface.market.alicloudapi.com/init";
				const formData = { initMsg: res.data };  

				uni.request({
					url:url,
					method:'POST',
					header:{
					'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
					'Authorization': 'APPCODE ',  // 替换为实际的 AppCode
					'X-Ca-Nonce': Math.round(Math.random() * 100000000).toString(),
					},
					data:formData,
					success: (res) => {
					        if (res.statusCode === 200) {
					          // 请求成功
							  let str:string="";
							  if (typeof res.data === 'string') {
							              str = res.data;
							            } else {
							              str = JSON.parse(JSON.stringify(res.data)).token;
							            }
								token=str;
					        } else {
					          // 请求失败
					          let str=res.data;
							  console.log(str);
					        }
					},
					fail: (err) => {
					        // 请求出错
					        },
					});
				
				
			},
			/**
			 * 开始人脸检测
			 */
			startLDT: function () {
				UTS_StartLivingDetect(token);
			}
			
		}
	}
</script>

<style>

  
</style>