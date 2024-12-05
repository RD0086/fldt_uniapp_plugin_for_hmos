<template>
	<view>
		<view class="checkbox-row">
			<checkbox-group @change="checkboxChange">
			  <label class="checkbox-label" v-for="(item, index) in items" :key="item.value">
				<checkbox :value="item.value" :checked="isChecked(item.value)" :disabled="disableCheckbox(item.value)" style="transform:scale(0.5)"/>
				<div class="checkbox-name">{{item.name}}</div>
			  </label>
			</checkbox-group>
		</view>
		<page-head :title="title"></page-head>
		<view class="uni-btn-v uni-common-mt">
			<button type="primary"  @tap="startLDT">开启人脸检测</button>
		</view>
		<div align="center">
	      <textarea :value="msg"/>
	    </div>
	</view>
</template>

<script lang="ts">
	import {UTS_Verify,UTS_StartLivingDetect,UTS_Exit,UTS_GetLDTVideo,UTS_RestartLdt,EsLivingDetectResult} from "@/uni_modules/esand-ldt"
	// 定义接口
	interface authSettingInterface {
	  livingType: number; // 活体类型  1：远近，2: 眨眼, 3：摇头，4: 点头，6：炫彩， 支持多动作，如传入12表示先做远近活体，后做眨眼活体，一次最多支持4组动作 
	  needVideo: boolean; // 是否需要录制视频， 默认为false
	  useStrictMode: number; // 是否使用严格模式  1：严格模式，0: 非严格模式，非严格模式下，炫彩环境检查不通过会使用其他的活体动作
	}
	
	interface configInterface extends authSettingInterface {
	  cameraDeviceId?: number; // 相机ID ， 0 : 后置摄像头，1：前置摄像头 (默认)
	  autoRedirects?:boolean; // 是否跳转到 returnURL 页面，如果为false, 那么不跳转，直接在调用页面返回执行结果， 请固定为false
	}
	
	interface HttpResponse {
	  code: number;
	  data: any;
	}
	
	export default {
		data() {
			return {
				title: '人脸活体检测Demo',
				msg: 'logs',
				stringParam:"人脸活体检测",
				items:
				 [{
					value: '1',
					name: '远近'
				  },
				  {
					value: '2',
					name: '眨眼'
				  },
				  {
					value: '3',
					name: '摇头'
				  },
				  {
					value: '4',
					name: '点头'
				  },
				  {
					value: '5',
					name: '张嘴'
				  }, 
				  {
					value: '6',
					name: '炫彩'
				  }
				],
				livingType: 0
			}
		},
		
		methods: {
			startLDT: async function () {
				/**
				 * 获取初始化token
				 */
				const configData: configInterface = {
				      livingType: parseInt(this.livingType.toString()),
				      needVideo: false,
				      useStrictMode: 1,
				      cameraDeviceId: 1,
							autoRedirects:false
				    };
					
				// 认证初始化
				let res:EsLivingDetectResult=await UTS_verifyInit(JSON.stringify(configData));
				const url = "https://eface.market.alicloudapi.com/init";
				const formData = { initMsg: res.data };  
				
				// 注意，为了保护APPCODE, 这段代码应该写到服务器端，然后经过服务器转发
				uni.request({
					url:url,
					method:'POST',
					header:{
					'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
					'Authorization': 'APPCODE ',  // 替换为实际的 AppCode
					'X-Ca-Nonce': Math.round(Math.random() * 100000000).toString(),
					},
					data:formData,
					success: async (res) => {
						if (res.statusCode === 200) {
								// 请求成功
							let str:string="";
							let that = this;
							if (typeof res.data === 'string') {
								str = res.data;
							} else {
								str = JSON.parse(JSON.stringify(res.data)).token;
							}
							/**
							 * 开始人脸活体检测
							 */
							UTS_StartLivingDetect(str).then(res => {
								that.msg = JSON.stringify(JSON.stringify(res));
								
								if(res.code==="ELD_SUCCESS"){
										console.log(that.msg)
										// 注意，为了保护APPCODE, 这段代码应该写到服务器端，然后经过服务器转发
										// 获取认证结果
										
										UTS_Exit(); // 主动退出页面
										return ;
									}
								});
							
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
			checkboxChange: function(evt) {
				let selectedValues = evt.detail.value;
				if (selectedValues.length > 4) {
					// 如果选择超过4个，则只保留前4个选择
					selectedValues = selectedValues.slice(0, 4);
				}
				// 更新数据，确保只存储最多4个选择
				this.livingType = parseInt(selectedValues.join(''));
			},
			
			isChecked: function(value) {
				return this.livingType.toString().includes(value);
			},
			disableCheckbox: function(value) {
				return this.livingType.toString().length >= 4 && !this.isChecked(value);
			}
			
		}
	}
</script>

<style>
.checkbox-row {
  display: flex;
  flex-wrap: nowrap; /* 禁止换行 */
  margin-top: 20rpx;
}

.checkbox-label {
  display: inline-flex;
  align-items: center;
  margin-right: 1px;
}

.checkbox-name {
  margin-left: 1px;
     font-size: 0.9rem;
}
textarea {
  margin-top: 20rpx;
  height: 800rpx;
  font-size: small;
}
</style>