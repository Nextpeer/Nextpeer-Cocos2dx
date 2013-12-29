package com.nextpeer.android.example;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/*  P2P (Player to Player) message used for sending messages over the wire.
 * 
 *  Right now the protocol demonstrates a way to pack the height position of each player,
 *  but you can extend it to send information about the player position, velocity and acceleration.
 */
public abstract class P2PMessage {
	
	// General protocol constants
	private static class Constants {
		public static final byte CURRENT_PROTOCOL_VERSION = 1; 
		private static final byte INT_SIZE = 4;
		private static final byte FLOAT_SIZE = 4;
		private static final byte BYTE_SIZE = 1; 
		private static final ByteOrder BYTE_ORDER = ByteOrder.BIG_ENDIAN; 
	}
	
	// Available message types
	public static class Types {
		public static final byte P2P_PLAYER_HEIGHT_SO_FAR = 1; 
	}
	
	// The type of the message
	public final byte type;
	
	// CTOR, initialize the message with its type
	private P2PMessage(byte type) {
		this.type = type;
	}
	
	// Try to decode the given message byte array into a P2PMessage.
	// @return null in case decode fail (invalid version, invalid size), Otherwise returns the P2PMessage object
	public static P2PMessage tryToDecodeOrNull(byte[] message) {
		if (message == null) return null;
		
		int messageLength = message.length;
		
		// The minimum message type (version + type + length in size 0)
		if (messageLength < Constants.BYTE_SIZE + Constants.BYTE_SIZE + Constants.INT_SIZE) return null;
		
		// Extract the version byte
		ByteBuffer bb = ByteBuffer.wrap(message);
		byte msgVersion = bb.get();
		
		// We not supporting backward compatibility
		if (msgVersion < Constants.CURRENT_PROTOCOL_VERSION) return null;
		
		
		// Extract the message type
		byte msgType = bb.get();
		byte[] msgData = null;
		int msgDataLength = bb.getInt();
		
		// Read the data if there is any
		if (msgDataLength > 0 && msgDataLength == bb.remaining()) {
			msgData = new byte[msgDataLength];
			bb.get(msgData);
		}
		
		P2PMessage decodedMessage = null;
		
		// Decode the message by its type if you can
		// Kind of Factory if you will.
		switch (msgType) {
			case Types.P2P_PLAYER_HEIGHT_SO_FAR : {
				decodedMessage = P2PMessagePlayerHeight.tryToDecodeFromDataOrNull(msgData);
				break;
			}
			default:
				break;
		}
		
		return decodedMessage;
	}
	
	// [byte][byte][int][*]
	// [version][type][data length][data]
	public byte[] encode() {
		byte[] data = getData();
		int encodedMessageSize = Constants.BYTE_SIZE + Constants.BYTE_SIZE + Constants.INT_SIZE + data.length; // version + type + dataLength + data
		return ByteBuffer.allocate(encodedMessageSize).order(Constants.BYTE_ORDER).put(Constants.CURRENT_PROTOCOL_VERSION).put(this.type).putInt(data.length).put(data).array();
	}
	
	// Abstract. Get the data of the subclass's members as byte array
	protected abstract byte[] getData();
	
	/*
	 *  P2P Messages
	 */
	
	/*
	 * Player movement message
	 */
	public static class P2PMessagePlayerHeight extends P2PMessage {
		public final float heightSoFar;
				
		// CTOR - initialize the player height message with heightSoFar
		public P2PMessagePlayerHeight(float heightSoFar) {
			super(Types.P2P_PLAYER_HEIGHT_SO_FAR);

			this.heightSoFar = heightSoFar;
		}

		@Override
		// [float]
		// [heightSoFar]
		protected byte[] getData() {
					
			int encodedMessageSize = Constants.FLOAT_SIZE;
			return ByteBuffer.allocate(encodedMessageSize).order(Constants.BYTE_ORDER).
					putFloat(this.heightSoFar).array();
		}
		
		// Decode the given data array into a valid message.
		// Return null in case the data length is invalid.
		protected static P2PMessagePlayerHeight tryToDecodeFromDataOrNull(byte[] data) {

			if (data == null) return null;
			
			int dataLength = data.length;
			
			// The minimum data type 
			if (dataLength <  Constants.FLOAT_SIZE) return null;

			// Position
			float msgHeightSoFar = ByteBuffer.wrap(data).getFloat(0);
			
			return new P2PMessagePlayerHeight(msgHeightSoFar);
		}
	}
}
