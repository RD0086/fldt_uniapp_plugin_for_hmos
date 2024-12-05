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
	//导入鸿蒙uts插件中的函数
	import {UTS_VerifyInit,UTS_StartLDT,EsLivingDetectResult} from "@/uni_modules/esand-ldt"
	// TODO 替换成您自己的APPCODE(切勿泄漏), 如何获取APPCODE,可参考：https://esandinfo.yuque.com/docs/share/13ad611e-b9c3-4cf8-a9a8-fe23a419312e?#
	 let ALIYUN_APPCODE = ''; // 阿里云网关APPCODE

	 // 从一砂云接入, 可参考文档： https://esandinfo.yuque.com/yv6e1k/aa4qsg/ghtqp7
	 let ES_APPCODE = 'TODO'; // 一砂云网关APPCODE
	 let ES_SECRET_KEY = 'TODO';// 一砂云网关密钥
	 let SECRET_KEY = '';

	interface authSettingInterface {
	  livingType: number; // 活体类型  1：远近，2: 眨眼, 3：摇头，4: 点头，6：炫彩， 支持多动作，如传入12表示先做远近活体，后做眨眼活体，一次最多支持4组动作
	  needVideo: boolean; // 是否需要录制视频， 默认为false
	  useStrictMode: number; // 是否使用严格模式  1：严格模式，0: 非严格模式，非严格模式下，炫彩环境检查不通过会使用其他的活体动作
	}

	interface configInterface extends authSettingInterface {
	  cameraDeviceId: number; // 相机ID ， 0 : 后置摄像头，1：前置摄像头 (默认)
	  autoRedirects: boolean; // 是否跳转到 returnURL 页面，如果为false, 那么不跳转，直接在调用页面返回执行结果， 请固定为false
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
				//初始化设置
				const configData: configInterface = {
				      livingType: parseInt(this.livingType.toString()),
				      needVideo: true,
				      useStrictMode: 1,
				      cameraDeviceId: 1,
					  autoRedirects:false,
				    };

				/**
				 * 1. 认证初始化
				 * @param options(JSONObject), 包括如下字段：
				 *		livingType：认证类型  1：远近，2：眨眼，3：摇头，4: 点头，5:张嘴，6：炫彩
				 *		needVideo: boolean; // 是否需要录制视频， 默认为false
				 *		useStrictMode: number; // 是否使用严格模式  1：严格模式，0: 非严格模式，非严格模式下，炫彩环境检查不通过会使用其他的活体动作
				 *		cameraDeviceId: number; // 相机ID ， 0 : 后置摄像头，1：前置摄像头 (默认)
				 *		autoRedirects:boolean; // 是否跳转到 returnURL 页面，如果为false, 那么不跳转，直接在调用页面返回执行结果， 请固定为false
				 * @return livingDetectResult 对象包括如下几个字段
				 * {
				 *    "code": "ELD_SUCCESS", -- ELD_SUCCESS：成功，ELD_FAILED：失败，ELD_PARAME_ERROR：参数异常，ELD_EXCEPTION：发生异常，ELD_UNSUPPORT：不支持此活体类型
				 *    "msg":"成功", -- 执行结果描述
				 *    "data": "......" -- 执行结果数据
				 * }
				 */
				console.log(JSON.stringify(configData));
				let res:EsLivingDetectResult = await UTS_VerifyInit(JSON.stringify(configData));
				const formData = { initMsg: res.data };
				console.log("初始化返回："+JSON.stringify(res));
				if(res.code!='ELD_SUCCESS'){
					this.msg ='活体检测初始化失败：'+res.msg
					return;
				}

				// 判断是从一砂云接入还是阿里云接入
				let serverURL = "https://edis.esandcloud.com/gateways?APPCODE=" + ES_APPCODE + "&ACTION=livingdetection/livingdetect/init";
				SECRET_KEY = ES_SECRET_KEY;
				if (ES_APPCODE == '' || ES_APPCODE == 'TODO') {
					serverURL = 'https://eface.market.alicloudapi.com/init';
					SECRET_KEY = ALIYUN_APPCODE;
				}

				let that=this;

				 /**
				 * 2. 请求阿里云初始化接口获取token（为了保护APPCODE,次端逻辑应该放在服务器端）
				 * 参考文档：https://market.aliyun.com/products/57124001/cmapi00046021.html#sku=yuncode4002100001
				 */
				// 注意，为了保护APPCODE, 这段代码应该写到服务器端，然后经过服务器转发

				uni.request({
					url:serverURL,
					method:'POST',
					header:{
					'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
					'Authorization': 'APPCODE ' + SECRET_KEY,  // 替换为实际的 AppCode
					'X-Ca-Nonce': Math.round(Math.random() * 100000000).toString(),
					},
					data:formData,
					success: async (res) => {
						if (res.statusCode === 200) {
								// 请求成功
							let str:string="";
							if (typeof res.data === 'string') {
								str = res.data;
							} else {
								str = JSON.parse(JSON.stringify(res.data)).token;
							}
							/**
							 * 3.发起活体检测
							 */
							UTS_StartLDT(str).then(livingDetectResult => {

								if(livingDetectResult.code==="ELD_SUCCESS"){
										console.log(that.msg)
										/**
										 * 4. 请求阿里云获取服务器端活体检测结果（为了保护APPCODE,次端逻辑应该放在服务器端）
										 * 参考文档：https://market.aliyun.com/products/57124001/cmapi00046021.html#sku=yuncode4002100001
										 */
										serverURL = "https://edis.esandcloud.com/gateways?APPCODE=" + ES_APPCODE + "&ACTION=livingdetection/livingdetect/verify";
										if (ES_APPCODE == '' || ES_APPCODE == 'TODO') {
											serverURL = 'https://eface.market.alicloudapi.com/verify';
											SECRET_KEY = ALIYUN_APPCODE;
										}

										uni.request({
											url: serverURL,
											method: 'POST',
											header: {
												// 注意，为了保护APPCODE, 这段代码应该写到服务器端，然后经过服务器转发
												'Authorization': 'APPCODE ' + SECRET_KEY,
												'X-Ca-Nonce': Math.round(Math.random() * 100000000).toString(),  // 防重放攻击
												'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
											},
											data: {
												//初始化接口返回参数
												'token': livingDetectResult.token,
												'verifyMsg': livingDetectResult.data,
											},
										success: (res) => {
											that.msg = '认证结果'+JSON.stringify(res.data);
										},
										});

									}
								});

						} else {
							// 请求失败
							let str=res.data;
							that.msg=JSON.stringify(str)
							console.log(str);

						}
					},
					fail: (err) => {
					        // 请求出错
							let str=err.errMsg;
							that.msg=JSON.stringify(str)
							console.log(str);
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
